/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** EHttpMethod
*/

/*!
 * \file EHttpMethod.hpp
 * \brief HTTP Methods.
 *
 * This file contains an enum and an associative array for all the HTTP methods.
 */

#pragma once

#include <unordered_map>

/*! \namespace Pizzia
 *
 * Namespace used for the Pizzia API
 */
namespace Pizzia {

	/*! \enum EHttpMethod
	 * \brief Constants used for HTTP Methods
	 */
	enum EHttpMethod {
		OPTIONS = 0, /*!< Request for information about the communication options available on the request/response chain identified by the Request-URI. */
		GET, /*!< Retrieve whatever information (in the form of an entity) is identified by the Request-URI. */
		HEAD, /*!< Identical to GET except that the server MUST NOT return a message-body in the response. */
		POST, /*!< Used to request that the origin server accept the entity enclosed in the request as a new subordinate of the resource identified by the Request-URI in the Request-Line. */
		PUT, /*!< Requests that the enclosed entity be stored under the supplied Request-URI. */
		DELETE, /*!< Requests that the origin server delete the resource identified by the Request-URI. */
		TRACE, /*!< Used to invoke a remote, application-layer loop- back of the request message. */
		CONNECT, /*!< For use with a proxy that can dynamically switch to being a tunnel (e.g. SSL tunneling). */
		UNDEFINED /*!< Undefined method. */
	};

	const std::unordered_map<std::string, EHttpMethod> methodMap = {
		{ "GET", GET },
		{ "OPTIONS", OPTIONS },
		{ "HEAD", HEAD },
		{ "POST", POST },
		{ "PUT", PUT },
		{ "DELETE", DELETE },
		{ "TRACE", TRACE },
		{ "CONNECT", CONNECT },
		{ "UNDEFINED", UNDEFINED }
	}; /*!< Map used to get the corresponding value from the EHttpMethod enum by an std::string. */

}