/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <memory>
#include "net/TCPClient.hpp"
#include "dems-api/Config.hpp"
#include "dems-api/Stage.hpp"
#include "ModulesManager.hpp"

#pragma once

namespace Zia {
class Client {
	public:
		Client(unsigned int id, std::shared_ptr<net::TCPClient> &sock, dems::config::Config &, ModulesManager &manager);
		~Client();

		Client() = delete;
		Client &operator=(const Client &) = delete;
		Client(const Client &) = delete;

	public:
		std::shared_ptr<net::TCPClient> getSocket() const { return _tcpClient; }
		void readMsg(const char *data, size_t size);
		void stop();
		void printMessage(const std::string &str);

	private:
		void discoverHookMap(dems::Stage::hookMap &map, dems::Context &context);

	private:
		unsigned int _id;
		std::shared_ptr<net::TCPClient> _tcpClient;
		dems::config::Config &_conf;
		ModulesManager &_manager;
		dems::Context _ctx;
};
}