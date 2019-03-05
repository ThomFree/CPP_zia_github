/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** ModulesManager
*/

#pragma once

#include "dems-api/AModulesManager.hpp"

namespace Zia::api {
class ModulesManager : public dems::AModulesManager {
public:
	ModulesManager() = default;
	~ModulesManager() = default;

	void loadModules(const std::string &directoryPath) override;
	void loadOneModule(const std::string &filePath) override;
	void unloadModule(const std::string &moduleName) override;
};
}
