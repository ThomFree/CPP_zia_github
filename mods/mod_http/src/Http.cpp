/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Http
*/

#include <sstream>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <experimental/filesystem>
#include <map>
#include "Http.hpp"
#include "dems-api/Heading.hpp"

namespace mod {

Http::Http(dems::Context &ctx) : _ctx(ctx)
{}

void Http::parse()
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

	// DEBUG
	std::cout << "DEBUG DU MSG RECU, firstLine : " << std::get<dems::header::Request>(_ctx.request.firstLine).method 
		<< ":" << std::get<dems::header::Request>(_ctx.request.firstLine).path << ":" 
		<< std::get<dems::header::Request>(_ctx.request.firstLine).httpVersion << std::endl;
	std::cout << "HEADERS :" << _ctx.request.headers->getWholeHeaders();
	std::cout << "BODY : /" << _ctx.request.body << "/" << std::endl;
}

void Http::interpretGet(std::string &code, std::string &msg, std::fstream &file)
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
	_ctx.response.headers->setHeader("Content-Type", "text/html");
}

void Http::interpretPost(std::string &, std::string &)
{
}

void Http::interpretHead(std::string &code, std::string &msg, std::fstream &file)
{
	std::string line;
	std::string buf;
	code = "200";
	msg = "OK";

	while (std::getline(file, line)) {
		buf.append(line);
  }

	_ctx.response.headers->setHeader("Content-Type", "text/html");
	//_ctx.response.headers->setHeader("Content-Length", std::to_string(buf.size()));  // /!\ POSTMAN doesn't get any response with this
}

void Http::interpretDelete(std::string &, std::string &)
{
}

void Http::interpretPut(std::string &, std::string &)
{

}

bool Http::isPathAvailable(std::string &code, std::string &msg, std::string &websitePath)
{
	auto modules = std::get<dems::config::ConfigObject>(_ctx.config["modules"].v);
	auto http = std::get<dems::config::ConfigObject>(modules["Http"].v);

	if (!(http.find("websitePath") == http.end())) {
			websitePath = std::get<std::string>(http["websitePath"].v);
	} else {
		dems::config::ConfigValue temp;

		temp.v = websitePath;
		std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(_ctx.config["modules"].v)["Http"].v)["websitePath"] = temp;
	}
	
	std::size_t found = websitePath.find_last_of("/");
  std::string lastDir = websitePath.substr(0,found);
	std::experimental::filesystem::create_directories(lastDir);

	bool isAccessible = true;

	if (websitePath.back() == '/')
		websitePath += "index.html";
	std::experimental::filesystem::perms perms(std::experimental::filesystem::status(websitePath).permissions());
	_file.open(websitePath, std::ios::in | std::ios::out | std::ios::binary);

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

void Http::interpret()
{
	_ctx.response.body = "";
	std::string msg = "";
	std::string code = "200";
	std::string websitePath = "./etc/zia/www/";


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

	std::vector<std::string>::const_iterator meth = std::find(_methodList.begin(), _methodList.end(), std::get<dems::header::Request>(_ctx.request.firstLine).method);

	if (meth != _methodList.end()) {
		if (*meth == "GET")
			interpretGet(code, msg, _file);
		else if (*meth == "POST")
			interpretPost(code, msg);
		else if (*meth == "PUT")
			interpretPut(code, msg);
		else if (*meth == "HEAD")
			interpretHead(code, msg, _file);
		else if (*meth == "DELETE")
			interpretDelete(code, msg);
	} else {
		msg = "Method Not Allowed. Allowed header : ";
		code = "405";
		for (auto it = _methodList.begin(); it != _methodList.end(); it++) {
			msg += *it;
		}
		msg += "\n";
	}
	_file.close();
	std::get<dems::header::Response>(_ctx.response.firstLine).message = msg;
	std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = code;
}

void Http::addToHeaders(const std::string &line)
{
	std::size_t i = line.find(": ");
	if (i == std::string::npos || i >= line.length() || i < 2)
		return;
	std::string key = line.substr(0, i);
	std::string value = line.substr(i + 2, line.length());

	if (key.length() > 0 && value.length() > 0)
		_ctx.request.headers->setHeader(key, value);
}

}