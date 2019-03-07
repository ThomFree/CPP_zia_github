/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigWatcher header
*/

#include <iostream>
#include <memory>
#include <efsw/efsw.hpp>
#include "Website.hpp"

#pragma once


namespace Zia {

	extern std::atomic<bool> RESTART_ZIA;

	class UpdateListener : public efsw::FileWatchListener
	{
	public:
		UpdateListener(std::list<std::shared_ptr<Website>> &sites, net::NetworkService &service);
		~UpdateListener() {}

		void handleFileAction(efsw::WatchID watchid, const std::string &dir, const std::string &filename,
		                      efsw::Action action, std::string oldFilename = "") final;

	private:
		std::list<std::shared_ptr<Website>> &_sites;
		net::NetworkService &_service;
	};

	class ConfigWatcher
	{
	public:
		ConfigWatcher(std::list<std::shared_ptr<Website>> &_sites, net::NetworkService &service);
		ConfigWatcher(std::list<std::shared_ptr<Website>> &_sites, net::NetworkService &service, const std::string &dirPath);
		~ConfigWatcher();

		efsw::WatchID setDirectory(const std::string &dirPath);

	private:
		efsw::FileWatcher *_fileWatcher;
		UpdateListener _updateListener;
		std::string _dirPath;
		efsw::WatchID _watchID;
	};

}
