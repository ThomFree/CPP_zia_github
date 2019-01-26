/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IModule
*/

#include "EModuleStatus.hpp"

#pragma once

namespace Pizzia {

class IModule {
	public:
		IModule() {}
		virtual ~IModule();

	public:
        virtual MODULE_STATUS execute() = 0;
};

}