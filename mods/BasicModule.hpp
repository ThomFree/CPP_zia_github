/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** BasicModule
*/

#include "api/IModule.hpp"

#pragma once
namespace Pizzia {

class BasicModule : public IModule {
	public:
		BasicModule() {}
		~BasicModule() {}

	public:
        EModuleStatus run(IRequest &request, IResponse &response, IMapContainer &configuration, IMapContainer &session) { return EModuleStatus::SUCCESS; }
		inline const std::string getName() const { return "BasicModule"; }
};

}