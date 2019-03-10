/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <iostream>
#include "Client.hpp"

namespace Zia {

Client::Client(unsigned int id, std::shared_ptr<net::ISocket> &sock,
		dems::config::Config &conf, ModulesManager &manager) : _id(id), _netClient(sock), _conf(conf), _manager(manager)
{
	_ctx.config = _conf;
	discoverStage(_manager.getStageManager().connection(), _ctx);
	_netClient->setDisconnect([&](net::ISocket *) { disconnect(); });
	_netClient->setReceive([&](const char *data, size_t size) { readMsg(data, size); });
}

Client::~Client()
{}

void Client::discoverStage(dems::Stage &stage, dems::Context &ctx)
{
	discoverHookMap(stage.firstHooks(), ctx);
	discoverHookMap(stage.middleHooks(), ctx);
	discoverHookMap(stage.endHooks(), ctx);
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

	printMessage(msg);
	_ctx.rawData.clear();
	for (unsigned int i = 0; i < size; i++)
		_ctx.rawData.push_back(data[i]);
	try {
		discoverStage(_manager.getStageManager().request(), _ctx);
	} catch (const std::exception &e) {
		std::cout << "Module crashed: " << e.what() << std::endl;
	}
	// TODO send le message (il faut convertir le ctx.response en rawData)
}

void Client::disconnect()
{
	discoverStage(_manager.getStageManager().disconnect(), _ctx);
}

void Client::stop()
{
	_netClient->disconnect();
}

void Client::printMessage(const std::string &str)
{
	std::string name(std::get<std::string>(_conf["name"].v));

	std::cout << "\t\t[Client " << _id << " (" << name << ")] -> " << str << std::endl;
}
}