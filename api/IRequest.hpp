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

namespace Pizzia {

	class IRequest {
	public:
		IRequest() = default;
		virtual ~IRequest();
	public:
		virtual const std::string &getRaw() = 0;
		virtual void setRaw(const std::string &raw) = 0;

		virtual EHttpMethod getMethod() const = 0;
		virtual void setMethod(EHttpMethod method) = 0;

		virtual const std::string &getUri() const = 0;
		virtual void setUri(const std::string &uri) = 0;

		virtual const IMapContainer &getParameters() const = 0;
		virtual void setParameters(const IMapContainer &parameters) = 0;

		virtual const std::pair<unsigned int, unsigned int> &getHttpVersion() const = 0;

		virtual const IMapContainer &getHeaders() const = 0;
		virtual void setHeaders(const IMapContainer &headers) = 0;

		virtual void setBody(const std::string &body) = 0;
	};
}