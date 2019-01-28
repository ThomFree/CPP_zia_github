/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IRequest
*/

#include <string>
#include <unordered_map>

#pragma once

namespace Pizzia {

	class IMapContainer {
	public:
		IMapContainer() {}
		virtual ~IMapContainer();
	public:
		virtual const std::string &getField(const std::string &key) const = 0;
		virtual setField(const std::string &key, const std::string &value) = 0;
		virtual bool hasField(const std::string &key) const = 0;
		virtual deleteField(const std::string &key) = 0;
	};
}