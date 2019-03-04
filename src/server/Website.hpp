/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Website
*/

#include <string>
#include "dems-api/Config.hpp"
#include "utils/JsonParser.hpp"
#include "net/NetworkService.hpp"
#include "net/TCPAcceptor.hpp"

#pragma once

namespace Zia {

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

	private:
		void checkConfig();
		void acceptClient(std::shared_ptr<net::TCPClient> client);

	private:
		std::string _filename;
		dems::config::Config _conf;
		JsonParser _jsonParser;
		net::TCPAcceptor _acceptor;
};

}