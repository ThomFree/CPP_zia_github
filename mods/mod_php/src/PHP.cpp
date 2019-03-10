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

	// DEBUG
	std::cout << "DEBUG DU MSG RECU, firstLine : " << std::get<dems::header::Request>(_ctx.request.firstLine).method 
		<< ":" << std::get<dems::header::Request>(_ctx.request.firstLine).path << ":" 
		<< std::get<dems::header::Request>(_ctx.request.firstLine).httpVersion << std::endl;
	std::cout << "HEADERS :" << _ctx.request.headers->getWholeHeaders();
	std::cout << "BODY : /" << _ctx.request.body << "/" << std::endl;
}

void PHP::interpret()
{
	// VALENTIN, le parse est fait et il te met les headers http, la methode, la version, l'uri et le body dans les variables de _ctx.request

	// Gestion d'erreur a faire sur method, uri, version
	//(en cas d'erreur il faut juste changer le message d'erreur dans le header de la response)
	//std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = 404 ou je sais pas quoi

	// Interpret context headers and do the request
	// Make the response
	_ctx.response.body = "HELLO WORLD.";
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

// TO KEEP
bool PHP::checkForPhp()
{
	// check if path is a directory and take index.php
	if (std::get<dems::header::Request>(_ctx.request.firstLine).path.find(".php") == std::string::npos)
		return false;
	// check url params and remove them
		// set _query it is a string
		// set _relativeFilePath
		// set _documentRoot

	// check errors on method and version

	_ctx.request.headers->setHeader("Cookie", "");

	setEnvironment();
	// call php cgi in a sub process (execve or something like that)
	// set reponse from the call to php cgi
}

void PHP::setEnvironment()
{
	_env.setHeader("DOCUMENT_ROOT", _documentRoot);
	_env.setHeader("QUERY_STRING", _query);

	_env.setHeader("HTTP_COOKIE", _ctx.request.headers.getHeader("Cookie"));
	_env.setHeader("HTTP_HOST", "127.0.0.1");
	_env.setHeader("HTTP_USER_AGENT", ctx.request.headers.getHeader(""));

	_env.setHeader("REQUEST_METHOD", "GET|HEAD|POST|PUT|DELETE|CREATE");
	_env.setHeader("REQUEST_URI", "uri");

	_env.setHeader("SCRIPT_FILENAME", "full pathname of the current cgi (index.php for example)");

	_env.setHeader("SERVER_PORT", "port in config");
	_env.setHeader("SERVER_SOFTWARE", "Zia/4.2");
	_env.setHeader("SERVER_PROTOCOL", "HTTP/1.1");

	_env.setHeader("CONTENT_TYPE", "in header");
	_env.setHeader("CONTENT_LENGTH", "size of the body or in the header");
}

}