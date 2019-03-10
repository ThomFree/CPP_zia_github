/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** PHP
*/

#include <sstream>
#include <iostream>
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
		_ctx.request.body = tmp.substr(tmp.find("\r\n\r\n"));

	// headers
	std::string line;
	std::getline(stream, line);
	while (std::getline(stream, line) && line.length() > 1) {
		addToHeaders(line);
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
	
	// DEBUG
	std::cout << _documentRoot << "+" << std::get<dems::header::Request>(_ctx.request.firstLine).path << ":" << _query << std::endl;

	// DEBUG
	// std::cout << "DEBUG DU MSG RECU, firstLine : " << std::get<dems::header::Request>(_ctx.request.firstLine).method 
	// 	<< ":" << std::get<dems::header::Request>(_ctx.request.firstLine).path << ":" 
	// 	<< std::get<dems::header::Request>(_ctx.request.firstLine).httpVersion << std::endl;
	// std::cout << "HEADERS :" << _ctx.request.headers->getWholeHeaders();
	// std::cout << "BODY : /" << _ctx.request.body << "/" << std::endl;
}

void PHP::addToHeaders(const std::string &line)
{
	std::size_t i = line.find(": ");
	if (i == std::string::npos || i >= line.length() || i < 2)
		return;
	std::string key = line.substr(0, i);
	std::string value = line.substr(i + 2, line.length());

	if (key.length() > 0 && value.length() > 0)
		_ctx.request.headers->setHeader(key, value);
}

bool PHP::checkForPhp()
{
	if (std::get<dems::header::Request>(_ctx.request.firstLine).path.find(".php") == std::string::npos)
		return false;
	const std::string &method = std::get<dems::header::Request>(_ctx.request.firstLine).method;
	if (method != "POST" && method != "GET" && method != "PUT" && method != "DELETE" && method != "HEAD") {
		std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = "405";
		std::get<dems::header::Response>(_ctx.response.firstLine).message = "Method not allowed.";
		return true;
	}
	if (std::get<dems::header::Request>(_ctx.request.firstLine).httpVersion != "HTTP/1.1") {
		std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = "400";
		std::get<dems::header::Response>(_ctx.response.firstLine).message = "Bad request.";
		return true;
	}
	setEnvironment();
	// call php cgi in a sub process (execve or something like that)
	// set reponse from the call to php cgi
	return true;
}

void PHP::setEnvironment()
{
	_env.setHeader("DOCUMENT_ROOT", _documentRoot);
	_env.setHeader("QUERY_STRING", _query);

	_env.setHeader("HTTP_COOKIE", _ctx.request.headers->getHeader("Cookie"));
	_env.setHeader("HTTP_HOST", "127.0.0.1");
	_env.setHeader("HTTP_USER_AGENT", _ctx.request.headers->getHeader("User-Agent"));

	_env.setHeader("REQUEST_METHOD", std::get<dems::header::Request>(_ctx.request.firstLine).method);
	_env.setHeader("REQUEST_URI", std::get<dems::header::Request>(_ctx.request.firstLine).path);

	_env.setHeader("SCRIPT_FILENAME", _documentRoot + std::get<dems::header::Request>(_ctx.request.firstLine).path);

	_env.setHeader("SERVER_SOFTWARE", "Zia/4.2");
	_env.setHeader("SERVER_PROTOCOL", "HTTP/1.1");

	_env.setHeader("CONTENT_TYPE", _ctx.request.headers->getHeader("Content-Type"));
	if (_ctx.request.headers->getHeader("Content-Length") == "")
		_ctx.request.headers->getHeader("Content-Length") = _ctx.request.body.size();
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
	// DEBUG
	std::cout << determineContentType(std::get<dems::header::Request>(_ctx.request.firstLine).path) << std::endl;
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

}