/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** ModulesManager
*/

#include <type_traits>

#include "ModulesManager.hpp"

namespace Zia {
ModulesManager::~ModulesManager()
{
//	for (auto &it : _mods) // --> SEGFAULT --> should be done after Stage has been deleted
//		delete it.second;
}

void ModulesManager::loadModules(const std::string &)
{
}

void ModulesManager::loadOneModule(const std::string &filePath)
{
	_mods.emplace(filePath, new DLLoader(filePath));
	_mods[filePath]->getEntryPoint<entryPoint>("registerHooks")(getStageManager());
}

void ModulesManager::unloadModule(const std::string &moduleName)
{
	getStageManager().request().unhookAll(moduleName);
	getStageManager().connection().unhookAll(moduleName);
	getStageManager().chunks().unhookAll(moduleName);
	getStageManager().disconnect().unhookAll(moduleName);
}
}