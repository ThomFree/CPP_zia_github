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
	DLLoader(filePath).getEntryPoint<entryPoint>("registerHooks")(getStageManager());
}

void ModulesManager::unloadModule(const std::string &moduleName)
{
	getStageManager().request().unhookAll(moduleName);
	getStageManager().connection().unhookAll(moduleName);
	getStageManager().chunks().unhookAll(moduleName);
	getStageManager().disconnect().unhookAll(moduleName);
}
}