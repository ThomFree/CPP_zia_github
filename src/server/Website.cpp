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
	while (_clients.size() > 0)
		_clients.pop_back();
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
	if (_acceptor.bind(std::get<long long>(_conf["port"].v))) {
		_acceptor.accept([this](std::shared_ptr<net::TCPClient> client) -> void { acceptClient(client); });
	}
	else {
		printMessage("Error while binding socket on port.");
		return;
	}
	printMessage("Started.");
	_state = RUNNING;
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

void Website::acceptClient(std::shared_ptr<net::TCPClient> sock)
{
	_clients.push_back(Client(_id++, sock, _conf));
}

void Website::stop()
{
	for (auto &client : _clients)
		client.stop();
}

}