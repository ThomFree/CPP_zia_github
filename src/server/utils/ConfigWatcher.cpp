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
		: _sites(sites), _service(service)
	{}

	void UpdateListener::handleFileAction(efsw::WatchID watchid, const std::string &dir, const std::string &filename,
	                                      efsw::Action action, std::string oldFilename)
	{
		std::string path = dir + filename;

		switch (action) {
			case efsw::Actions::Add:
				std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added" << std::endl;
				break;
			case efsw::Actions::Delete:
				std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete" << std::endl;
				break;
			case efsw::Actions::Modified:
				std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Modified" << std::endl;
				for (auto it = _sites.begin(); it != _sites.end(); ++it) {
					auto site = (*it);
					if (path == site->filename) {
						site->stop();
						_sites.erase(it);
//						_sites.push_back(std::make_shared<Website> (path, _service));
						return;
					}
				}
				break;
			case efsw::Actions::Moved:
				std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from (" << oldFilename
				          << ")" << std::endl;
				break;
			default:
				std::cout << "Should never happen!" << std::endl;
		}
	}

	/*
	 * ConfigWatcher
	 */

	ConfigWatcher::ConfigWatcher(std::list<std::shared_ptr<Website>> &sites, net::NetworkService &service)
		: _fileWatcher(new efsw::FileWatcher), _updateListener(new UpdateListener(sites, service)) {}

	ConfigWatcher::ConfigWatcher(std::list<std::shared_ptr<Website>> &sites, net::NetworkService &service, const std::string &dirPath)
		: _fileWatcher(new efsw::FileWatcher), _updateListener(new UpdateListener(sites, service))
	{
		this->setDirectory(dirPath);
	}

	efsw::WatchID ConfigWatcher::setDirectory(const std::string &dirPath)
	{
		this->_dirPath = dirPath;
		this->_watchID = this->_fileWatcher->addWatch(_dirPath, this->_updateListener.get(), true);
		this->_fileWatcher->watch();
		return this->_watchID;
	}
}