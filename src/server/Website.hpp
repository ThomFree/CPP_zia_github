/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Website
*/

#include <string>
#include "api/Config.hpp"

#pragma once

namespace Zia {

class Website {
	public:
		Website(const std::string &filename);
		~Website();

		Website() = delete;
		Website &operator=(const Website&) = delete;
		Website(const Website&) = delete;

	private:
		std::string _filename;
		dems::config::Config _conf;
		// JSON Parsing class
};

}