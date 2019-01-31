/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** HelloModule
*/

#include "api/IModule.hpp"

#pragma once
namespace Pizzia {

class HelloModule : public IModule {
	public:
		HelloModule() {}
		~HelloModule() {}

	public:
        EModuleStatus run(IRequest &, IResponse &, IMapContainer &, IMapContainer &);
		inline const std::string getName() const { return "HelloModule"; }
};

}