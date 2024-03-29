/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** WebsiteManager
*/

#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include "WebsiteManager.hpp"

namespace Zia {

static void displayStopService()
{
	std::cout << "[Zia] Service interrupted by user." << std::endl;
}

WebsiteManager::WebsiteManager(ParseArgs &parser)
	: _parser(parser), _confPath(""), _service(&displayStopService), _configWatcher(_sites, _service)
{
	if (_parser.argExist("-p")) {
		std::cout << "[Zia] Site configuration path found in arguments: " << _parser.getArg("-p") << std::endl;
		_confPath = _parser.getArg("-p");
	}
	else
		std::cout << "[Zia] Site configuration path not found, default value set : ./etc/zia/sites " << std::endl;
}

WebsiteManager::~WebsiteManager()
{
	stop();
	while (_sites.size() > 0)
		_sites.pop_back();
	std::cout << "[Zia] Stopped." << std::endl;
}

void WebsiteManager::launch()
{
	exploreDirectory();
	_configWatcher.setDirectory(_confPath);
	for (auto &site : _sites) {
		try {
			site->launch();
		} catch (const std::exception &e) {
			std::cout << e.what() << std::endl;
			continue;
		}
	}
	// Ici start le cmdline et le interpretReceivedCmd pour executer les commandes
	// le file auto updater (relaod de la config d'un website à partir de la maj de sa config) ?

	std::cout << "[Zia] Started." << std::endl << std::endl;

	int nb = 0;
	for (const auto &site : _sites)
		if (site->getState() == RUNNING)
			nb += 1;
	if (nb == 0) {
		std::cout << "[Zia] Nothing is listenning." << std::endl;
		return;
	} else
		_service.run();

	std::cout << std::endl << "[Zia] Stopping..." << std::endl;
}

void WebsiteManager::stop()
{
	for (auto &site : _sites)
		site->stop();
	_service.stop();
}

void WebsiteManager::exploreDefaultDirectory()
{
	_confPath = "./etc/zia/sites";
	try {
		for(auto& file: std::experimental::filesystem::directory_iterator(_confPath)) {
			if (std::experimental::filesystem::is_regular_file(file))
				try {
					auto ptr = std::make_shared<Website> (file.path(), _service);
					_sites.push_back(ptr);
				} catch (const std::exception &err) {
					std::cout << "[Zia] Failed to create " << file.path() << " website: " << err.what() << std::endl;
				}
		}
	} catch (const std::experimental::filesystem::filesystem_error &fsErr) {
		std::cout << "[Zia] An error occurred while trying to open " << _confPath << ": " << fsErr.what() << std::endl;
	}
	if (_sites.size() == 0)
		createDefaultWebsite();
}

void WebsiteManager::exploreDirectory()
{
	if (_confPath == "./etc/zia/sites" || _confPath == "") {
		exploreDefaultDirectory();
		return;
	}
	try {
		for(auto& file: std::experimental::filesystem::directory_iterator(_confPath)) {
			if (std::experimental::filesystem::is_regular_file(file))
				try {
					auto ptr = std::make_shared<Website> (file.path(), _service);
					_sites.push_back(ptr);
				} catch (const std::exception &err) {
					std::cout << "[Zia] Failed to create " << file.path() << " website: " << err.what() << std::endl;
				}
		}
	} catch (const std::experimental::filesystem::filesystem_error &fsErr) {
		std::cout << "[Zia] An error occurred while trying to open " << _confPath << ": " << fsErr.what() << std::endl;
		std::cout << "[Zia] Site configuration path invalid, setting default value : ./etc/zia/sites " << std::endl;
		exploreDefaultDirectory();
		return;
	}
	if (_sites.size() == 0)
		createDefaultWebsite();
}

void WebsiteManager::createDefaultWebsite()
{
	std::cout << "[Zia] No websites were found." << std::endl;
	std::cout << "[Zia] Creating a default website: " << _confPath + "/defaultSite.json" << std::endl;
	_confPath = "./etc/zia/sites";
	std::experimental::filesystem::create_directories("./etc/zia/sites");
	std::ofstream ofs(_confPath + "/defaultSite.json", std::ofstream::out);
	ofs << "{\n\t\"name\": \"BasicHttpSite\",\n\t\"port\": 8080,\n\t\"modules\": {}\n}\n";
	ofs.close();
	_sites.push_back(std::make_shared<Website> (_confPath + "/defaultSite.json", _service));
}

}