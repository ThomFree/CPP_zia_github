/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IModule
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
	 * \brief The interface class used for the creation of the different modules.
	 */
	class IModule {
	public:
		/*!
		 * \fn IModule()
		 * \brief Constructor
		 * \details Constructor of the IModule interface class.
		 */
		IModule() = default;

		/*!
		 * \fn virtual ~IModule()
		 * \brief Destructor
		 * \details Destructor of the IModule interface class.
		 */
		virtual ~IModule();

	public:
		/*!
		 * \fn virtual static EModuleStatus run(IRequest &request, IResponse &response, IKeyValueContainer &configuration, IKeyValueContainer &session)
		 * \brief Run the module and return its status.
		 * \details This virtual function, which need to be overwritten, will run the module and return the status of it.
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
		 * \details This virtual function, which need to be overwritten, will simply return a string corresponding to the module name.
		 * \return The module name, which is of type std::string.
		 */
		virtual const std::string getName() const = 0;
	};
}