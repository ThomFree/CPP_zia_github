/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IModule
*/

#include "EModuleStatus.hpp"
#include "IRequest.hpp"
#include "IResponse.hpp.hpp"
#include "IKeyValueContainer.hpp"

#pragma once

namespace Pizzia {
	class IModule {
	public:
		IModule() {}
		virtual ~IModule();

	public:
		virtual static EModuleStatus run(
			IRequest &request,
			IResponse &response,
			IKeyValueContainer &configuration,
			IKeyValueContainer &session
		) = 0;

		virtual static const std::string &getName() const;
	};
}