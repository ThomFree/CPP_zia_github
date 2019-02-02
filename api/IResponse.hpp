/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IResponse
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

	/*! \class IResponse
	 * \brief The interface class used for the responses.
	 */
	class IResponse {
	public:
		/*!
		 * \fn IResponse()
		 * \brief Constructor.
		 * \details Constructor of the IResponse interface class.
		 */
		IResponse() {}
		/*!
		 * \fn virtual ~IResponse()
		 * \brief Destructor.
		 * \details Destructor of the IResponse interface class.
		 */
		virtual ~IResponse() {}

	public:
		/*!
		 * \fn virtual const std::string &getRaw() const
		 * \brief Get the raw data of the response.
		 * \details Return an std::string corresponding to the raw data of the response.
		 *
		 * \return The raw data, which is of type std::string.
		 */
		virtual const std::string &getRaw() const = 0;
		/*!
		 * \fn virtual void setRaw(const std::string &raw)
		 * \brief Set the raw data of the response.
		 * \details Allow to set the raw data of the response from an std::string.
		 *
		 * \param raw The raw data to be set, which is of type std::string.
		 */
		virtual void setRaw(const std::string &raw) = 0;

		/*!
		 * \fn virtual unsigned int getStatusCode() const
		 * \brief Get the status code of the response.
		 * \details Return an unsigned int corresponding to the status code of the response.
		 *
		 * \return The status code, which is of type unsigned int.
		 */
		virtual unsigned int getStatusCode() const = 0;
		/*!
		 * \fn virtual void setStatusCode(unsigned int statusCode)
		 * \brief Set the status code of the response.
		 * \details Allow to set the status code of the response from an unsigned int.
		 *
		 * \param statusCode The status code to be set, which is of type unsigned int.
		 */
		virtual void setStatusCode(unsigned int statusCode) = 0;

		/*!
		 * \fn virtual const std::string &getStatusReasonPhrase() const
		 * \brief Get the status reason phrase of the response.
		 * \details Return an std::string corresponding to the status reason phrase of the response.
		 *
		 * \return The status reason phrase, which is of type std::string.
		 */
		virtual const std::string &getStatusReasonPhrase() const = 0;
		/*!
		 * \fn virtual void setStatusReasonPhrase(const std::string &reasonPhrase)
		 * \brief Set the status reason phrase of the response.
		 * \details Allow to set the status reason phrase of the response from an std::string.
		 *
		 * \param reasonPhrase The status reason phrase to be set, which is of type std::string.
		 */
		virtual void setStatusReasonPhrase(const std::string &reasonPhrase) = 0;

		/*!
		 * \fn virtual const std::pair<unsigned int, unsigned int> &getHttpVersion() const
		 * \brief Get the HTTP version of the response.
		 * \details Return an std::pair (of unsigned int and unsigned int) corresponding to the HTTP version of the response.
		 *
		 * \return The HTTP version, which is of type std::pair<unsigned int, unsigned int>.
		 */
		virtual const std::pair<unsigned int, unsigned int> &getHttpVersion() const = 0;
		/*!
		 * \fn virtual void setHttpVersion(unsigned int major, unsigned int minor)
		 * \brief Set the HTTP version of the response.
		 * \details Allow to set the HTTP version of the response from an std::pair (of unsigned int and unsigned int).
		 *
		 * \return The HTTP version to be set, which is of type std::pair<unsigned int, unsigned int>.
		 */
		virtual void setHttpVersion(unsigned int major, unsigned int minor) = 0;

		/*!
		 * \fn virtual IMapContainer &getHeaders()
		 * \brief Get the headers of the response.
		 * \details Return an IMapContainer object corresponding to the headers of the response.
		 *
		 * \return The headers, which are of type IMapContainer.
		 */
		virtual IMapContainer &getHeaders() = 0;

		/*!
		 * \fn virtual const std::string &getBody() const
		 * \brief Get the body of the response.
		 * \details Return an std::string corresponding to the body of the response.
		 *
		 * \return The body, which is of type std::string
		 */
		virtual const std::string &getBody() const = 0;
		/*!
		 * \fn virtual void setBody(const std::string &body)
		 * \brief Set the body of the response.
		 * \details Allow to set the body of the response from an std::string.
		 *
		 * \param body The body to set, which is of type std::string.
		 */
		virtual void setBody(const std::string &body) = 0;
	};
}