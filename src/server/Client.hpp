/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <memory>
#include "dems-api/Config.hpp"
#include "dems-api/Stage.hpp"
#include "dems-api/Heading.hpp"
#include "ModulesManager.hpp"
#include "net/ISocket.hpp"

#pragma once

namespace Zia {
class Client {
	public:
		Client(unsigned int id, std::shared_ptr<net::ISocket> &sock, dems::config::Config &, ModulesManager &manager);
		~Client();

		Client() = delete;
		Client &operator=(const Client &) = delete;
		Client(const Client &) = delete;

	public:
		std::shared_ptr<net::ISocket> getSocket() const { return _netClient; }
		void readMsg(const char *data, size_t size);
		void stop();
		void disconnect();
		void printMessage(const std::string &str);

	private:
		void discoverHookMap(dems::Stage::hookMap &map, dems::Context &context);
		void discoverStage(dems::Stage &stage, dems::Context &ctx);

	private:
		unsigned int _id;
		std::shared_ptr<net::ISocket> _netClient;
		dems::config::Config _conf;
		ModulesManager &_manager;
		dems::Context _ctx;
};
}