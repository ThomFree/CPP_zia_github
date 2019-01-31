/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IRequest
*/

#include <string>
#include <unordered_map>

#include "EHttpMethod.hpp"
#include "IMapContainer.hpp"

#pragma once

/*! \namespace Pizzia
 *
 * Namespace used for the Pizzia API
 */
namespace Pizzia {

	/*! \class IRequest
	 * \brief The interface class used for the requests.
	 */
	class IRequest {
	public:
		/*!
		 * \fn IRequest()
		 * \brief Constructor
		 * \details Constructor of the IRequest interface class.
		 */
		IRequest() = default;

		/*!
		 * \fn virtual ~IRequest()
		 * \brief Destructor
		 * \details Destructor of the IRequest interface class.
		 */
		virtual ~IRequest();

	public:
		/*!
		 * \fn virtual const std::string &getRaw() const
		 * \brief Get the raw data of the request.
		 * \details This function, which need to be overwritten, will return an std::string corresponding to the raw data of the request.
		 *
		 * \return The raw data, which is of type std::string.
		 */
		virtual const std::string &getRaw() const = 0;
		/*!
		 * \fn virtual void setRaw(const std::string &raw)
		 * \brief Set the raw data of the request.
		 * \details This function, which need to be overwritten, will allow to set the raw data of the request from an std::string.
		 *
		 * \param raw The raw data to be set, which is of type std::string.
		 */
		virtual void setRaw(const std::string &raw) = 0;

		/*!
		 * \fn virtual EHttpMethod getMethod() const
		 * \brief Get the method of the request.
		 * \details This function, which need to be overwritten, will return a value from the EHttpMethod enum corresponding to the method of the request.
		 *
		 * \return The method, which is a value from the EHttpMethod enum.
		 */
		virtual EHttpMethod getMethod() const = 0;
		/*!
		 * \fn virtual void setMethod(EHttpMethod method)
		 * \brief Set the method of the request.
		 * \details This function, which need to be overwritten, will allow to set the method of the request from a value of the EHttpMethod enum.
		 *
		 * \param method The method to be set, which is a value of the EHttpMethod enum.
		 */
		virtual void setMethod(EHttpMethod method) = 0;

		/*!
		 * \fn virtual const std::string &getUri() const
		 * \brief Get the URI of the request.
		 * \details This function, which need to be overwritten, will return an std::string corresponding to the URI of the request.
		 *
		 * \return The URI, which is of type std::string.
		 */
		virtual const std::string &getUri() const = 0;
		/*!
		 * \fn virtual void setUri(const std::string &uri)
		 * \brief Set the URI of the request.
		 * \details This function, which need to be overwritten, will allow to set the URI of the request from an std::string.
		 *
		 * \param uri The URI to be set, which is of type std::string.
		 */
		virtual void setUri(const std::string &uri) = 0;

		/*!
		 * \fn virtual const IMapContainer &getParameters() const
		 * \brief Get the parameters of the request.
		 * \details This function, which need to be overwritten, will return an IMapContainer object corresponding to the parameters of the request.
		 *
		 * \return The parameters, which are of type IMapContainer.
		 */
		virtual const IMapContainer &getParameters() const = 0;
		/*!
		 * \fn virtual void setParameters(const IMapContainer &parameters)
		 * \brief Set the parameters of the request.
		 * \details This function, which need to be overwritten, will allow to set the parameters of the request from an IMapContainer object.
		 *
		 * \param parameters The parameters to be set, which are of type IMapContainer.
		 */
		virtual void setParameters(const IMapContainer &parameters) = 0;

		/*!
		 * \fn virtual const std::pair<unsigned int, unsigned int> &getHttpVersion() const
		 * \brief Get the HTTP version of the request.
		 * \details This function, which need to be overwritten, will return an std::pair (of unsigned int and unsigned int) corresponding to the HTTP version of the request.
		 *
		 * \return The HTTP version, which is of type std::pair<unsigned int, unsigned int>.
		 */
		virtual const std::pair<unsigned int, unsigned int> &getHttpVersion() const = 0;
		/*!
		 * \fn virtual void setHttpVersion(unsigned int major, unsigned int minor)
		 * \brief Set the HTTP version of the request.
		 * \details This function, which need to be overwritten, will allow to set the HTTP version of the request from an std::pair (of unsigned int and unsigned int).
		 *
		 * \return The HTTP version to be set, which is of type std::pair<unsigned int, unsigned int>.
		 */
		virtual void setHttpVersion(unsigned int major, unsigned int minor) = 0;

		/*!
		 * \fn virtual const IMapContainer &getHeaders() const
		 * \brief Get the headers of the request.
		 * \details This function, which need to be overwritten, will return an IMapContainer object corresponding to the headers of the request.
		 *
		 * \return The headers, which are of type IMapContainer.
		 */
		virtual const IMapContainer &getHeaders() const = 0;
		/*!
		 * \fn virtual void setHeaders(const IMapContainer &headers)
		 * \brief Set the headers of the request.
		 * \details This function, which need to be overwritten, will allow to set the headers of the request from an IMapContainer object.
		 *
		 * \param headers The headers to be set, which are of type IMapContainer.
		 */
		virtual void setHeaders(const IMapContainer &headers) = 0;

		/*!
		 * \fn virtual void setBody(const std::string &body)
		 * \brief Set the body of the request.
		 * \details This function, which need to be overwritten, will allow to set the body of the request from an std::string.
		 *
		 * \param body The body to set, which is of type std::string.
		 */
		virtual void setBody(const std::string &body) = 0;
		virtual const std::string &getBody() const = 0;
	};
}