/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigWatcher header
*/

#include "ConfigWatcher.hpp"

namespace Zia {
	/*
	 * UpdateListener
	 */

	UpdateListener::UpdateListener(std::list<std::shared_ptr<Zia::Website>> &sites, net::NetworkService &service)
		: _sites(sites), _service(service) {}

	void UpdateListener::handleFileAction([[maybe_unused]] efsw::WatchID watchid,
	                                      const std::string &dir,
	                                      const std::string &filename,
	                                      [[maybe_unused]] efsw::Action action,
	                                      [[maybe_unused]] std::string oldFilename)
	{
		std::string path = dir + filename;

		RESTART_ZIA = true;
		_service.stop();
	}

	/*
	 * ConfigWatcher
	 */

	ConfigWatcher::ConfigWatcher(std::list<std::shared_ptr<Website>> &sites, net::NetworkService &service)
		: _fileWatcher(new efsw::FileWatcher), _updateListener(sites, service) {}

	ConfigWatcher::ConfigWatcher(std::list<std::shared_ptr<Website>> &sites, net::NetworkService &service,
	                             const std::string &dirPath)
		: _fileWatcher(new efsw::FileWatcher), _updateListener(sites, service)
	{
		this->setDirectory(dirPath);
	}

	ConfigWatcher::~ConfigWatcher()
	{
		delete this->_fileWatcher;
	}

	efsw::WatchID ConfigWatcher::setDirectory(const std::string &dirPath)
	{
		this->_dirPath = dirPath;
		this->_watchID = this->_fileWatcher->addWatch(_dirPath, &this->_updateListener, true);
		this->_fileWatcher->watch();
		return this->_watchID;
	}
}