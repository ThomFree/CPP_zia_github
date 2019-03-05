/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <iostream>
#include "Client.hpp"

namespace Zia {

Client::Client(unsigned int id, std::shared_ptr<net::TCPClient> &sock,
		dems::config::Config &conf, ModulesManager &manager) : _id(id), _tcpClient(sock), _conf(conf), _manager(manager) // TODO recevoir la config, les modules
{
	// TODO creer un context vierge ici
	// TODO start la pipeline des modules de connection
	_tcpClient->socket()->setReceive([&](const char *data, size_t size) { readMsg(data, size); });
}

Client::~Client()
{
	// TODO start la pipeline des modules de deco
}

void Client::readMsg(const char *data, size_t size)
{
	std::string msg(data, size);

	// DEBUG
	printMessage(msg);
	// TODO remplir le context des donnees recues
	// TODO start la pipeline des modules de request ici
}

void Client::stop()
{
	_tcpClient->socket()->disconnect();
}

void Client::printMessage(const std::string &str)
{
	std::string name(std::get<std::string>(_conf["name"].v));

	std::cout << "\t\t[Client " << _id << " (" << name << ")] -> " << str << std::endl;
}
}