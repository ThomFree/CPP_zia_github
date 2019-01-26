/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniMediator
*/

#include <vector>
#include "api/IModule.hpp"

#pragma once

namespace Pizzia {

class MiniMediator {
	public:
		MiniMediator();
		~MiniMediator();

	public:
        void runModules();

    private:
        void readData();
        std::vector<IModule> _modules;
};

}