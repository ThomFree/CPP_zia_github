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
	 * \brief Constants used for getting/setting the status of a module.
	 */
	enum EModuleStatus {
		SUCCESS, /*!< Module is successfully running. */
		ERROR, /*!< Module has encountered an error. */
		FATAL_ERROR, /*!< Module has encountered a critical error. */
	};

}