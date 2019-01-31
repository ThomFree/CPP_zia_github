/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** RequestParser
*/

#include <sstream>
#include <regex>
#include "RequestParser.hpp"

//DEBUG
#include <iostream>

namespace Pizzia {

void RequestParser::_removeWhitespace(std::string &line)
{
	line = std::regex_replace(line, std::regex("^ +"), "");
	line = std::regex_replace(line, std::regex(" +$"), "");
}

void RequestParser::_addInHeader(IRequest &request, std::string line)
{	
	std::size_t i = line.find(":");
	std::string key = line.substr(0, i);
	std::string value = line.substr(i + 1, line.length());

	_removeWhitespace(key);
	_removeWhitespace(value);

	//TODO
	// Ajouter dans la map de header
	//request.getHeaders().create(key, value);
}

bool RequestParser::_setHttpVersion(IRequest &request, std::string version)
{
	std::regex r("([0-9]+)");
	std::smatch smatch;
	std::vector<unsigned int> versions;

	while (std::regex_search(version, smatch, r)) {
		std::cout << smatch.str() << std::endl;
		versions.push_back(std::stoi(smatch.str()));
		version = smatch.suffix();
	}

	if (versions.size() != 2) {
		// TODO Log une erreur
		std::cout << "Bad header" << std::endl;
		return false;
	} else {
		request.setHttpVersion(version[0], version[1]);
		return true;
	}
}

EModuleStatus RequestParser::run(IRequest &request, IResponse &response, IMapContainer &configuration, IMapContainer &session)
{
	std::stringstream stream(request.getRaw());
	std::string method;
	std::string uri;
	std::string version;
	std::string line;

	stream >> method;
	stream >> uri;
	stream >> version;

	//DEBUG
	std::cout << "Method : " << method << std::endl;
	std::cout << "URI : " << uri << std::endl;
	std::cout << "Version : " << version << std::endl;
	//END DEBUG

	if (_setHttpVersion(request, version) == false) {
		return EModuleStatus::ERROR;
	}
	while (std::getline(stream, line, '\n')) {
		if (line.length() > 1) {
			_addInHeader(request, line);
		}
	}
	return EModuleStatus::SUCCESS;
}

}