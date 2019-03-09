/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** PHP
*/

#include "HttpHeader"
#include "dems-api/Stage.hpp"

#pragma once

namespace mod {

class PHP {
	public:
		PHP(dems::Context &ctx);
		~PHP() = default;

		PHP() = delete;
		PHP &operator=(const PHP &) = delete;
		PHP(const PHP &) = delete;

	public:
		void parse();
		void interpret();

		// TO KEEP
		bool checkForPhp();
	private:
		void setEnvironment();

	private:
		void addToHeaders(const std::string &line);

	private:
		dems::Context &_ctx;

		// TO KEEP
		HttpHeader _env;
};

}