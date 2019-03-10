/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Http
*/

#include "dems-api/Stage.hpp"
#include <map>
#include <functional>
#include <algorithm>
#include <fstream>


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
		void addToHeaders(const std::string &line);
		void interpretGet(std::string &code, std::string &msg, std::fstream &file);
		void interpretHead(std::string &code, std::string &msg, std::fstream &file);
		void interpretPut(std::string &code, std::string &msg);
		void interpretDelete(std::string &code, std::string &msg);
		void interpretPost(std::string &code, std::string &msg);
		bool isPathAvailable(std::string &code, std::string &msg, std::string &websitePath);

	private:
		dems::Context &_ctx;
		const std::vector<std::string> _methodList = {"GET", "HEAD", "POST", "//OPTIONS", "PUT", "DELETE", "//TRACE" };
		std::fstream _file;
		
};

}