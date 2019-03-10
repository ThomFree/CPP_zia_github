/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Website
*/

#include <string>
#include <vector>

#include "dems-api/Config.hpp"
#include "utils/JsonParser.hpp"
#include "net/NetworkService.hpp"
#include "net/TCPAcceptor.hpp"
#include "Client.hpp"

#pragma once

namespace Zia {

enum {
	STOPPED,
	RUNNING
};

static inline const net::SSLConf getSSLConf(dems::config::Config &conf)
{
	net::SSLConf ssl;
	for (auto &sslObj : std::get<dems::config::ConfigObject>(conf["ssl"].v)) {
		if (sslObj.first == "certificate") {
			ssl.certFile = std::get<std::string>((sslObj.second.v));
		} else if (sslObj.first == "private_key") {
			ssl.keyFile = std::get<std::string>((sslObj.second.v));
		} else if (sslObj.first == "dh") {
			ssl.dhFile = std::get<std::string>((sslObj.second.v));
		} else if (sslObj.first == "verify_mode") {
			ssl.verifFile = std::get<std::string>((sslObj.second.v));
		} else {
			throw std::runtime_error("Unknown parameter");
		}
	}
	return ssl;
}

class Website {
	public:
		Website(const std::string &filename, net::NetworkService &net);
		~Website();

		Website() = delete;
		Website &operator=(const Website&) = delete;
		Website(const Website&) = delete;

	public:
		void launch();
		void printMessage(const std::string &str);
		int getState() const { return _state; }
		void stop();

	private:
		void checkConfig();
		void acceptClient(std::shared_ptr<net::ISocket> client);
		void instantiateModules();

	private:
		const std::string _filename;
		dems::config::Config _conf;
		JsonParser _jsonParser;
		net::TCPAcceptor _acceptor;
		std::vector<std::unique_ptr<Client>> _clients;
		int _state = STOPPED;
		unsigned int _id = 0;
		ModulesManager _manager;
		net::SSLConf _sslConf;
};

}