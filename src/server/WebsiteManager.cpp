/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** WebsiteManager
*/

#include <iostream>
#include "WebsiteManager.hpp"

namespace Zia {

WebsiteManager::WebsiteManager(ParseArgs &parser) : _parser(parser), _confPath("/etc/zia/sites/")
{
	std::cout << "[Zia] Started." << std::endl;
	if (_parser.argExist("-p")) {
		std::cout << "[Zia] Site configuration path found in arguments: " << _parser.getArg("-p") << std::endl;
	}
}

WebsiteManager::~WebsiteManager()
{
	// Ici start le cmdline et le interpretReceivedCmd pour executer les commandes
	// le file auto updater ?
	std::cout << "[Zia] Stopped." << std::endl;
}

void WebsiteManager::exploreDirectory()
{
	// explore directory
		// for each file
			// try to create a new website if successful, put it in the vector
			// else log the error
	// if invalid direcotry, try default one
}

void WebsiteManager::launch()
{
	exploreDirectory();
	// TODO Start tous les sites avec leur config
	std::cout << "[Zia] Stopping..." << std::endl;
}

}