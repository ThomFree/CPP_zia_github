/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** PHP
*/

#include <sstream>
#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <experimental/filesystem>
#include <map>
#include <unordered_map>
#include "HttpHeader.hpp"
#include "dems-api/Stage.hpp"

#pragma once

namespace mod {

	const std::unordered_map<std::string, std::string> TYPES = {
		{".bz", "application/x-bzip"},
		{".bz2", "application/x-bzip2"},
		{".css", "text/css"},
		{".csv", "text/csv"},
		{".gif", "image/gif"},
		{".htm", "text/html"},
		{".ico", "image/ico"},
		{".jar", "application/java-archive"},
		{"jpeg", "image/jpeg"},
		{"jpg", "image/jpeg"},
		{".js", "application/javascript"},
		{".json", "application/json"},
		{".png", "image/png"},
		{".pdf", "application/pdf"},
		{".rar", "application/x-rar-compressed"},
		{".svg", "image/svg+xml"},
		{".swf", "application/x-shockwave-flash"},
		{".tar", "application/x-tar"},
		{".ts", "application/typescript"},
		{".xhtml", "application/xhtml+xml"},
		{".xml", "application/xml"},
		{".zip", "application/zip"},
		{".7z", "application/x-7z-compressed"}
	};

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
		bool checkForPhp();

	private:
		std::string determineContentType(const std::string &str);
		void setEnvironment();
		void addToHeaders(const std::string &line);
		void interpretGet(std::string &code, std::string &msg, std::fstream &file);
		bool isPathAvailable(std::string &code, std::string &msg, std::string &websitePath);

	private:
		dems::Context &_ctx;
		Zia::HttpHeader _env;
		std::string _query;
		std::string _documentRoot;
		std::fstream _file;
};

}