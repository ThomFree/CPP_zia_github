/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <iostream>
#include "Client.hpp"

namespace Zia {

Client::Client(unsigned int id, std::shared_ptr<net::TCPClient> &sock, dems::config::Config &conf) : _id(id), _tcpClient(sock), _conf(conf) // TODO recevoir les modules
{
	_tcpClient->socket()->setReceive([&](const char *data, size_t size) { readMsg(data, size); });
}

Client::~Client()
{
}

void Client::readMsg(const char *data, size_t size)
{
	std::string msg(data, size);

	// DEBUG
	printMessage(msg);
	// TODO start les modules ici (toute la pipeline)
}

void Client::stop()
{
	_tcpClient->socket()->disconnect();
}

void Client::printMessage(const std::string &str)
{
	std::string name(std::get<std::string>(_conf["name"].v));

	std::cout << "\t\t[Client (" << name << ")] -> " << str << std::endl;
}

}