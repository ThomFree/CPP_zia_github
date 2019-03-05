/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** WebsiteManager
*/

#include <list>
#include <memory>

#include "utils/ParseArgs.hpp"
#include "net/NetworkService.hpp"
#include "Website.hpp"

#pragma once

namespace Zia {

class WebsiteManager {
	public:
		WebsiteManager(ParseArgs &parser);
		~WebsiteManager();

		WebsiteManager() = delete;
		WebsiteManager &operator=(const WebsiteManager &) = delete;
		WebsiteManager(const WebsiteManager &) = delete;

	public:
		void launch();
		void stop();

	private:
		void exploreDirectory();
		void exploreDefaultDirectory();
		void createDefaultWebsite();

	private:
		ParseArgs &_parser;
		std::string _confPath;
		net::NetworkService _service;
		std::list<std::shared_ptr<Website>> _sites;
};

}