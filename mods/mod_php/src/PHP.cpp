/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** PHP
*/

#include <sstream>
#include <iostream>
#include <algorithm>
#include "PHP.hpp"
#include "dems-api/Heading.hpp"

namespace mod {

PHP::PHP(dems::Context &ctx) : _ctx(ctx)
{}

void PHP::parse()
{
	std::string tmp;
	for (size_t i = 0; i < _ctx.rawData.size(); i++)
		tmp.append(1, static_cast<char>(_ctx.rawData[i]));
	
	// firstLine
	std::stringstream stream(tmp);
	stream >> std::get<dems::header::Request>(_ctx.request.firstLine).method;
	stream >> std::get<dems::header::Request>(_ctx.request.firstLine).path;
	stream >> std::get<dems::header::Request>(_ctx.request.firstLine).httpVersion;

	// body
	if (tmp.find("\r\n\r\n") != std::string::npos)
		_ctx.request.body = tmp.substr(tmp.find("\r\n\r\n") + 4);

	// headers
	std::string line;
	std::getline(stream, line);
	while (std::getline(stream, line) && line.length() > 1) {
		addToHeaders(line, *_ctx.request.headers);
	}
}

void PHP::addToHeaders(std::string line, dems::header::IHeaders &hdr)
{
	line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
	std::size_t i = line.find(": ");
	if (i == std::string::npos || i >= line.length() || i < 2)
		return;
	std::string key = line.substr(0, i);
	std::string value = line.substr(i + 2, line.length());
	if (key.length() > 0 && value.length() > 0)
		hdr.setHeader(key, value);
}

bool PHP::checkForPhp()
{
	if (std::get<dems::header::Request>(_ctx.request.firstLine).httpVersion != "HTTP/1.1" 
	|| std::get<dems::header::Request>(_ctx.request.firstLine).path.size() < 1) {
		std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = "400";
		std::get<dems::header::Response>(_ctx.response.firstLine).message = "Bad request.";
		return true;
	}
	const std::string &method = std::get<dems::header::Request>(_ctx.request.firstLine).method;
	if (method != "POST" && method != "GET" && method != "PUT" && method != "DELETE" && method != "HEAD") {
		std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = "405";
		std::get<dems::header::Response>(_ctx.response.firstLine).message = "Method not allowed.";
		return true;
	}
	// querystring
	if (std::get<dems::header::Request>(_ctx.request.firstLine).path.find("?") != std::string::npos) {
		_query = std::get<dems::header::Request>(_ctx.request.firstLine).path.substr(std::get<dems::header::Request>(_ctx.request.firstLine).path.find("?") + 1);
		std::get<dems::header::Request>(_ctx.request.firstLine).path = std::get<dems::header::Request>(_ctx.request.firstLine).path.substr(0, std::get<dems::header::Request>(_ctx.request.firstLine).path.find("?"));
	}

	// path
	if (std::get<dems::header::Request>(_ctx.request.firstLine).path.back() == '/')
		std::get<dems::header::Request>(_ctx.request.firstLine).path.append("index.php");
	auto mod = std::get<dems::config::Config>(_ctx.config["modules"].v);
	auto php = std::get<dems::config::Config>(mod["PHP"].v);
	if (php.find("websitePath") != php.end())
		_documentRoot = std::get<std::string>(php["websitePath"].v);
	else
		_documentRoot = "etc/zia/wwwPhp/";

	if (std::get<dems::header::Request>(_ctx.request.firstLine).path.find(".php") == std::string::npos)
		return false;
	setEnvironment();

	try {
		std::string tmp;
		std::string res;

		for (const auto &pair : _env.getMap()) {
			tmp += "export \"" + pair.first + "=" + pair.second + "\";";
		}
		res += exec(tmp + "echo -e \"" + _ctx.request.body + "\" | php-cgi \"" + _documentRoot + std::get<dems::header::Request>(_ctx.request.firstLine).path + "\"");
		if (res.find("\r\n\r\n") != std::string::npos)
			_ctx.response.body = res.substr(res.find("\r\n\r\n"));
		else
			_ctx.response.body = res;
		std::stringstream stream(res);
		std::string line;
		std::getline(stream, line);
		while (std::getline(stream, line) && line.length() > 1) {
			addToHeaders(line, *_ctx.response.headers);
		}
		std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = "200";
		std::get<dems::header::Response>(_ctx.response.firstLine).message = "OK";
		return true;
	} catch (...) {
		std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = "502";
		std::get<dems::header::Response>(_ctx.response.firstLine).message = "Internal Server error.";
		return true;
	}
	return true;
}

void PHP::setEnvironment()
{
	_env.setHeader("DOCUMENT_ROOT", _documentRoot);
	_env.setHeader("QUERY_STRING", _query);
	_env.setHeader("REDIRECT_STATUS", "false");

	_env.setHeader("HTTP_COOKIE", _ctx.request.headers->getHeader("Cookie"));
	_env.setHeader("HTTP_HOST", "127.0.0.1");
	_env.setHeader("HTTP_USER_AGENT", _ctx.request.headers->getHeader("User-Agent"));

	_env.setHeader("REQUEST_METHOD", std::get<dems::header::Request>(_ctx.request.firstLine).method);
	_env.setHeader("REQUEST_URI", std::get<dems::header::Request>(_ctx.request.firstLine).path);

	_env.setHeader("SCRIPT_FILENAME", _documentRoot + std::get<dems::header::Request>(_ctx.request.firstLine).path);

	_env.setHeader("SERVER_SOFTWARE", "Zia/4.2");
	_env.setHeader("SERVER_PROTOCOL", "HTTP/1.1");

	_env.setHeader("CONTENT_TYPE", _ctx.request.headers->getHeader("Content-Type"));
	_env.setHeader("CONTENT_LENGTH", _ctx.request.headers->getHeader("Content-Length"));
}

void PHP::interpretGet(std::string &code, std::string &msg, std::fstream &file)
{
	std::string line;
	std::string buffer;
	
	while (std::getline(file, line)) {
		buffer.append(line);
	}
	file.clear();
	file.seekg(0, std::ios::beg);
	code = "200";
	msg = "OK";
	_ctx.response.body = buffer;
	_ctx.response.headers->setHeader("Content-Type", determineContentType(std::get<dems::header::Request>(_ctx.request.firstLine).path));
	_ctx.response.headers->setHeader("Content-Length", std::to_string(buffer.size()));
}

bool PHP::isPathAvailable(std::string &code, std::string &msg, std::string &websitePath)
{
	auto modules = std::get<dems::config::ConfigObject>(_ctx.config["modules"].v);
	auto http = std::get<dems::config::ConfigObject>(modules["PHP"].v);

	if (!(http.find("websitePath") == http.end())) {
			websitePath = std::get<std::string>(http["websitePath"].v);
	} else {
		dems::config::ConfigValue temp;

		temp.v = websitePath;
		std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(_ctx.config["modules"].v)["PHP"].v)["websitePath"] = temp;
	}
	
	std::size_t found = websitePath.find_last_of("/");
	std::string lastDir = websitePath.substr(0,found);
	std::experimental::filesystem::create_directories(lastDir);

	bool isAccessible = true;

	std::experimental::filesystem::perms perms(std::experimental::filesystem::status(websitePath).permissions());
	_file.open(websitePath + std::get<dems::header::Request>(_ctx.request.firstLine).path, std::ios::in | std::ios::out | std::ios::binary);

	if (!_file.good()) {
		code = "404";
		msg = "Not Found";
		isAccessible = false;
	} if ((perms & std::experimental::filesystem::perms::owner_read) == std::experimental::filesystem::perms::none &&
		(perms & std::experimental::filesystem::perms::owner_write) == std::experimental::filesystem::perms::none)	{
		code = "403";
		msg = "Forbidden";
		isAccessible = false;
	}
	return isAccessible;
}

void PHP::interpret()
{
	_ctx.response.body = "";
	std::string msg = "";
	std::string code = "200";
	std::string websitePath = "./etc/zia/wwwPhp/";


	if (std::get<dems::header::Request>(_ctx.request.firstLine).httpVersion != "HTTP/1.1") {
		std::get<dems::header::Response>(_ctx.response.firstLine).message = "Bad Request. HTTP 1.1 Required";
		std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = "400";
		return ;
	}
	std::get<dems::header::Response>(_ctx.response.firstLine).httpVersion = std::get<dems::header::Request>(_ctx.request.firstLine).httpVersion;


	if (!isPathAvailable(code, msg, websitePath)) {
		std::get<dems::header::Response>(_ctx.response.firstLine).message = msg;
		std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = code;
		return ;
	}

	if (std::get<dems::header::Request>(_ctx.request.firstLine).method == "GET") {
		interpretGet(code, msg, _file);
	} else {
		msg = "Method Not Allowed. Allowed header : GET";
		code = "405";
		msg += "\r\n";
	}
	_file.close();
	std::get<dems::header::Response>(_ctx.response.firstLine).message = msg;
	std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = code;
}

std::string PHP::determineContentType(const std::string &str)
{
	for (const auto &pair : TYPES) {
		if (str.find(pair.first) != std::string::npos)
			return pair.second;
	}
	return "text/html";
}

std::string PHP::exec(const std::string &cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("execution failed");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

}