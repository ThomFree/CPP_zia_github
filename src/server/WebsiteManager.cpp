/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** WebsiteManager
*/

#include <iostream>
#include <filesystem>
#include <fstream>

#include "WebsiteManager.hpp"

namespace Zia {

WebsiteManager::WebsiteManager(ParseArgs &parser) : _parser(parser), _confPath("")
{
	std::cout << "[Zia] Started." << std::endl;
	if (_parser.argExist("-p")) {
		std::cout << "[Zia] Site configuration path found in arguments: " << _parser.getArg("-p") << std::endl;
		_confPath = _parser.getArg("-p");
	}
	else
		std::cout << "[Zia] Site configuration path not found, default value set : /etc/zia/sites/ " << std::endl;
}

WebsiteManager::~WebsiteManager()
{
	std::cout << "[Zia] Stopped." << std::endl;
}

void WebsiteManager::launch()
{
	exploreDirectory();
	// TODO Start tous les sites avec leur config
	// Mettre tous les websites sur le netservice (les accept)

	// Ici start le cmdline et le interpretReceivedCmd pour executer les commandes
	// le file auto updater ?
	// Launch le io_service du websiteManager
	// Catch du ctrl-c par le io_service ou suite a un "stop()" sur le io_service
	std::cout << "[Zia] Stopping..." << std::endl;
}

void WebsiteManager::exploreDefaultDirectory()
{
	_confPath = "/etc/zia/sites/";
	try {
		for(auto& file: std::filesystem::directory_iterator(_confPath)) {
			if (file.is_regular_file())
				try {
					auto ptr = std::make_shared<Website> (_confPath);
					_sites.push_back(ptr);
				} catch (const std::exception &err) {
					std::cout << "[Zia] Failed to create " << _confPath << " website: " << err.what() << std::endl;
				}
		}
	} catch (const std::filesystem::filesystem_error &fsErr) {
		std::cout << "[Zia] An error occurred while trying to open " << _confPath << ": " << fsErr.what() << std::endl;
	}
	if (_sites.size() == 0)
		createDefaultWebsite();
}

void WebsiteManager::exploreDirectory()
{
	if (_confPath == "/etc/zia/sites/" || _confPath == "") {
		exploreDefaultDirectory();
		return;
	}
	try {
		for(auto& file: std::filesystem::directory_iterator(_confPath)) {
			if (file.is_regular_file())
				try {
					auto ptr = std::make_shared<Website> (_confPath);
					_sites.push_back(ptr);
				} catch (const std::exception &err) {
					std::cout << "[Zia] Failed to create " << _confPath << " website: " << err.what() << std::endl;
				}
		}
	} catch (const std::filesystem::filesystem_error &fsErr) {
		std::cout << "[Zia] An error occurred while trying to open " << _confPath << ": " << fsErr.what() << std::endl;
		std::cout << "[Zia] Site configuration path invalid, setting default value : /etc/zia/sites/ " << std::endl;
		exploreDefaultDirectory();
		return;
	}
	if (_sites.size() == 0)
		createDefaultWebsite();
}

void WebsiteManager::createDefaultWebsite()
{
	std::cout << "[Zia] No websites were found." << std::endl;
	std::cout << "[Zia] Creating a default website: " << _confPath + "defaultSite.json" << std::endl;
	_confPath = "/etc/zia/sites/";
	std::filesystem::create_directories("/etc/zia/sites/");
	std::ofstream ofs(_confPath + "defaultSite.json", std::ofstream::out);
	ofs << "{\n\t\"name\": \"BasicHttpSite\",\n\t\"port\": 8080,\n\t\"modules\": {}\n}\n";
	_sites.push_back(std::make_shared<Website> (_confPath + "defaultSite.json"));
}

}