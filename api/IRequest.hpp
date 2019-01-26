/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IRequest
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
    virtual EHttpMethod getMethod() const = 0;

    virtual const std::string &getUri() const = 0;

    virtual const std::unordered_map<std::string, std::string> &getParams() const = 0;

    virtual const std::pair<unsigned int, unsigned int> &getVersion() const = 0;

    virtual const std::string &getRaw();

    // TODO rajouter getter et setter pour header et body
};

}