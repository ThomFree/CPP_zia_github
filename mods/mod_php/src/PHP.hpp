/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** PHP
*/

#include "server/HttpHeader"
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
		std::string _query;
		std::string _documentRoot;
		std::string _relativeFilePath;
};

}