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
		dems::config::Config &conf, ModulesManager &manager) : _id(id), _tcpClient(sock), _conf(conf), _manager(manager)
{
	_ctx.config = conf;
	discoverHookMap(_manager.getStageManager().connection().firstHooks(), _ctx);
	_tcpClient->socket()->setReceive([&](const char *data, size_t size) { readMsg(data, size); });
}

Client::~Client()
{
	discoverHookMap(_manager.getStageManager().connection().endHooks(), _ctx);
}

void Client::discoverHookMap(dems::Stage::hookMap &map, dems::Context &context)
{
	for (auto &elem : map) {
		elem.second.callback(context);
	}
}

void Client::readMsg(const char *data, size_t size)
{
	std::string msg(data, size);

	// DEBUG
	printMessage(msg);
	// TODO parse received message in _ctx
	discoverHookMap(_manager.getStageManager().connection().middleHooks(), _ctx);
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