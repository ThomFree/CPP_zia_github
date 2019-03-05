/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** ModulesManager
*/

#include <memory>
#include <unordered_map>

#include "dems-api/AModulesManager.hpp"
#include "utils/DLLoader.hpp"

#pragma once

namespace Zia {
class ModulesManager : public dems::AModulesManager {
	public:
		using entryPoint = std::string (*)(dems::StageManager &);
		ModulesManager() = default;
		~ModulesManager() noexcept;

		void loadModules(const std::string &directoryPath) override;
		void loadOneModule(const std::string &filePath) override;
		void unloadModule(const std::string &moduleName) override;

	private:
		std::unordered_map<std::string, DLLoader*> _mods;
};
}
