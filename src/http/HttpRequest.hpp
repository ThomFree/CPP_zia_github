/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** HttpRequest
*/

#include <string>
#include "api/IRequest.hpp"
#include "http/MapContainer.hpp"

#pragma once

namespace Pizzia {

class HttpRequest : public IRequest {
	public:
		HttpRequest(const std::string &raw) : _raw(raw) {}
		~HttpRequest() {}

    public:
        const std::string &getRaw() const final { return _raw; }
		void setRaw(const std::string &raw) final { _raw = raw; }

        EHttpMethod getMethod() const final { return _method; }
		void setMethod(EHttpMethod method) final { _method = method; }

		const std::string &getUri() const final { return _uri; }
		void setUri(const std::string &uri) final { _uri = uri; }

		const IMapContainer &getParameters() const final { return _params; }
        // COMMENT QUON FAIT ICI ??????????????????????????????
		void setParameters(const IMapContainer &parameters) final { _params = (MapContainer)parameters; }

		const std::pair<unsigned int, unsigned int> &getHttpVersion() const final { return _version; }
        void setHttpVersion(unsigned int major, unsigned int minor) final { _version = std::make_pair(major, minor);}

		const IMapContainer &getHeaders() const final;
		void setHeaders(const IMapContainer &headers) final;

		void setBody(const std::string &body) final;
		const std::string &getBody() const final;

    private:
        std::string _raw;
        EHttpMethod _method;
        std::string _uri;
        MapContainer _params;
        std::pair<unsigned int, unsigned int> _version;
};

}