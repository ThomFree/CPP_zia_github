/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Http
*/

#include "dems-api/Stage.hpp"

#pragma once

namespace mod {

class Http {
	public:
		Http(dems::Context &ctx);
		~Http() = default;

		Http() = delete;
		Http &operator=(const Http &) = delete;
		Http(const Http &) = delete;

	public:
		void parse();
		void interpret();

	private:
		dems::Context &_ctx;
};

}