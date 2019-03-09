/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Http
*/

#include <sstream>
#include <iostream>
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

void Http::interpret()
{
	// VALENTIN, le parse est fait et il te met les headers http, la methode, la version, l'uri et le body dans les variables de _ctx.request

	// Gestion d'erreur a faire sur method, uri, version
	//(en cas d'erreur il faut juste changer le message d'erreur dans le header de la response)
	//std::get<dems::header::Response>(_ctx.response.firstLine).statusCode = 404 ou je sais pas quoi

	// Interpret context headers and do the request
	// Make the response
	_ctx.response.body = "HELLO WORLD.";
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