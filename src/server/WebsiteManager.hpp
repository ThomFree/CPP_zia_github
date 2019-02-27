/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** WebsiteManager
*/

#include <list>

#include "utils/ParseArgs.hpp"
#include "dems-api/Config.hpp"
//#include "Website.hpp"

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
		void exploreDirectory();

	private:
		//std::list<Website> _sites;
		ParseArgs &_parser;
		std::string _confPath;
};

}