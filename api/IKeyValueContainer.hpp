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

	class IKeyValueContainer {
	public:
		IMapContainer() {}
		virtual ~IMapContainer();
	public:
		virtual setValue(const std::string &key, const std::string &value) = 0;
		virtual setValue(const std::string &key, int value) = 0;
		virtual setValue(const std::string &key, float value) = 0;
		virtual setValue(const std::string &key, bool value) = 0;

		virtual const std::string &getStringValue(const std::string &key) const = 0;
		virtual int getIntValue(const std::string &key) const = 0;
		virtual float getFloatValue(const std::string &key) const = 0;
		virtual bool getBoolValue(const std::string &key) const = 0;
	};
}