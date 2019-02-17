/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** EModuleStatus
*/

/*!
 * \file EModuleStatus.hpp
 * \brief Status of a module.
 *
 * This file contains a simple enum for the status of a module.
 */

#pragma once

/*! \namespace Pizzia
 *
 * Namespace used for the Pizzia API
 */
namespace Pizzia {

	/*! \enum EModuleStatus
	 * \brief Constants used for getting the returned status of a module.
	 */
	enum EModuleStatus {
		SUCCESS, /*!< Module is successfully running. */
		ERROR, /*!< An error occurred, module flow was interrupted but a response message is sent to the client. */
		FATAL_ERROR, /*!< An unrecoverable error occurred, module flow was interrupted and the server sends nothing to the client. */
	};

}