/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Website
*/

#include <iostream>
#include "Website.hpp"

namespace Zia {

Website::Website(const std::string &filename, net::NetworkService &net) : _filename(filename), _conf(), _jsonParser(_filename), _acceptor(net)
{
	_conf = _jsonParser.makeConfigFromJson();
	checkConfig();
	// TODO instantiate all the modules from the file
	// if everything is good start to accept connection
	printMessage("Prepared.");
}

Website::~Website()
{
	printMessage("Stopped.");
}

void Website::printMessage(const std::string &str)
{
	if (_conf.find("name") == _conf.end())
		std::cout << "\t[Website - " + _filename + "] " << str << std::endl;
	else
		std::cout << "\t[Website - " << std::get<std::string>(_conf["name"].v) << "] " << str << std::endl;
}

void Website::launch()
{
	std::cout << "la" << std::endl;
	if (_acceptor.bind(std::get<long long>(_conf["port"].v))) {
		std::cout << "lla" << std::endl;
		_acceptor.accept([this](std::shared_ptr<net::TCPClient> client) -> void { std::cout << "dedans"<< std::endl; });
		std::cout << "llla" << std::endl;
	}
	else
		printMessage("Error while binding socket on port");
	printMessage("Started.");
}

void Website::checkConfig()
{
	if (_conf.find("name") == _conf.end() || _conf.find("port") == _conf.end() || _conf.find("modules") == _conf.end())
		throw std::runtime_error("Name or port or modules variable does not appear in your configuration.");
	if (std::get<long long>(_conf["port"].v) > 1 || std::get<long long>(_conf["port"].v) < 65535)
		return;
	if ((_conf["name"]).v.index() == JsonParser::TYPE::STRING && (_conf["port"]).v.index() == JsonParser::TYPE::LONG 
		&& (_conf["modules"]).v.index() == JsonParser::TYPE::OBJECT)
		return;
	throw std::runtime_error("Please verify your configuration, something went wrong.");
}

void Website::acceptClient(std::shared_ptr<net::TCPClient>)
{
	std::cout << "oui" << std::endl;
}

}