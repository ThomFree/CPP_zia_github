/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IModule
*/

/*!
 * \file IModule.hpp
 * \brief Websites modules.
 *
 * This file contains an IModule interface used for the instantiation of the websites modules.
 */

#include "EModuleStatus.hpp"
#include "IRequest.hpp"
#include "IResponse.hpp"

#pragma once

/*! \namespace Pizzia
 *
 * Namespace used for the Pizzia API
 */
namespace Pizzia {
	/*! \class IModule
	 * \brief The interface used for the instantiation of the different modules of a website.
	 */
	class IModule {
	public:
		/*!
		 * \fn IModule()
		 * \brief Constructor.
		 * \details Constructor of the IModule interface.
		 */
		IModule() {}

		/*!
		 * \fn virtual ~IModule()
		 * \brief Destructor.
		 * \details Destructor of the IModule interface.
		 */
		virtual ~IModule() {}

	public:
		/*!
		 * \fn virtual static EModuleStatus run(IRequest &request, IResponse &response, IKeyValueContainer &configuration, IKeyValueContainer &session)
		 * \brief Run the module and return its status.
		 * \details Run the module and return its status.
		 *
		 * \param request A class derived from IRequest.
		 * \param response A class derived from IResponse.
		 * \param configuration The configuration of the server.
		 * \param session The session of the server.
		 * \return The module status, which is a value from the EModuleStatus enum.
		 */
		virtual EModuleStatus run(
			IRequest &request,
			IResponse &response,
			IMapContainer &configuration,
			IMapContainer &session
		) = 0;

		/*!
		 * \fn virtual static const std::string &getName() const
		 * \brief Get the module name.
		 * \details Simply return an std::string corresponding to the module name.
		 *
		 * \return The module name, which is of type std::string.
		 */
		virtual const std::string getName() const = 0;
	};
}