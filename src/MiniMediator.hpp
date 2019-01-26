/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniMediator
*/

#include <vector>
#include "api/IModule.hpp"

#pragma once

class MiniMediator {
	public:
		MiniMediator();
		~MiniMediator();

	public:
        void runModules();

    private:
        //std::vector<IModule> _modules;
};