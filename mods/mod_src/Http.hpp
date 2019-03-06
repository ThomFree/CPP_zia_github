/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Http
*/

#include "dems-api/Stage.hpp"

#pragma once

class Http {
	public:
		using key = std::string;
		using value = std::string;
		Http(dems::Context &ctx);
		~Http() = default;

	private:
		dems::Context &_ctx;
		std::unordered_map<s
};
