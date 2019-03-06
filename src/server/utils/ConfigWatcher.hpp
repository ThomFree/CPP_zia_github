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

	class UpdateListener : public efsw::FileWatchListener
	{
	public:
		UpdateListener(std::list<std::shared_ptr<Website>> &sites, net::NetworkService &service);

		void handleFileAction(efsw::WatchID watchid, const std::string &dir, const std::string &filename,
		                      efsw::Action action, std::string oldFilename = "");

	private:
		std::list<std::shared_ptr<Website>> &_sites;
		net::NetworkService &_service;
	};

	class ConfigWatcher
	{
	public:
		ConfigWatcher(std::list<std::shared_ptr<Website>> &_sites, net::NetworkService &service);

		ConfigWatcher(std::list<std::shared_ptr<Website>> &_sites, net::NetworkService &service, const std::string &dirPath);

		~ConfigWatcher() = default;

		efsw::WatchID setDirectory(const std::string &dirPath);

	private:
		std::unique_ptr<efsw::FileWatcher> _fileWatcher;
		std::unique_ptr<UpdateListener> _updateListener;
		std::string _dirPath;
		efsw::WatchID _watchID;
	};

}
