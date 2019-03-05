/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** ModulesManager
*/

#include <filesystem>

#include "ModulesManager.hpp"

namespace Zia {
void ModulesManager::loadModules(const std::string &)
{

}

void ModulesManager::loadOneModule(const std::string &filePath)
{
	DLLoader(filePath).getEntryPoint<entryPoint>("registerHooks");
}

void ModulesManager::unloadModule(const std::string &moduleName)
{
	stageManager_.request().unhookAll(moduleName);
	stageManager_.connection().unhookAll(moduleName);
	stageManager_.chunks().unhookAll(moduleName);
	stageManager_.disconnect().unhookAll(moduleName);
}
}