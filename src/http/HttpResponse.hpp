/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** HttpResponse
*/

#include <string>
#include "api/IResponse.hpp"
#include "http/MapContainer.hpp"

#pragma once

namespace Pizzia {

class HttpResponse : public IResponse {
	public:
		HttpResponse() {}
		~HttpResponse() {}
		HttpResponse &operator=(const HttpResponse &) = delete;
		HttpResponse(const HttpResponse &) = delete;

    public:
        const std::string &getRaw() const final { return _raw; }
		void setRaw(const std::string &raw) final { _raw = raw; }

		const std::pair<unsigned int, unsigned int> &getHttpVersion() const final { return _version; }
        void setHttpVersion(unsigned int major, unsigned int minor) final { _version = std::make_pair(major, minor);}

		IMapContainer &getHeaders() final { return _headers; }

		unsigned int getStatusCode() const { return _statusCode; }
		void setStatusCode(unsigned int statusCode) { _statusCode = statusCode; }
	
		const std::string &getStatusReasonPhrase() const { return _reasonPhrase; }
		void setStatusReasonPhrase(const std::string &reasonPhrase) { _reasonPhrase = reasonPhrase; }

		const std::string &getBody() const final { return _body; }
		void setBody(const std::string &body) final { _body = body; }



    private:
        std::string _raw;
		MapContainer _headers;
		std::string _body;
        std::pair<unsigned int, unsigned int> _version;
		std::string _reasonPhrase;
		unsigned int _statusCode;
};

}