/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IResponse
*/

#include <string>
#include <unordered_map>

#include "EHttpMethod.hpp"

#pragma once

namespace Pizzia {

class IRequest {
	public:
		IRequest() {}
		virtual ~IRequest();

  public:
    virtual unsigned int getStatusCode() const = 0;
    virtual void setStatusCode(unsigned int statusCode) = 0;

    virtual const std::string &getStatusReasonPhrase() const = 0;
    virtual void setStatusReasonPhrase(const std::string &reasonPhrase) = 0;

    virtual const std::pair<unsigned int, unsigned int> &getVersion() const = 0;
    virtual const std::pair<unsigned int, unsigned int> &setVersion() const = 0;

    // TODO rajouter getter pour header et body
};

}