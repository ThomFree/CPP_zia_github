/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** ParseArgs
*/

#include <vector>
#include <string>
#include <unordered_map>

#pragma once

namespace Zia {

class ParseArgs {
	public:
		ParseArgs(int ac, const char * const av[]);
		~ParseArgs() = default;

		ParseArgs() = delete;
		ParseArgs &operator=(const ParseArgs &) = delete;
		ParseArgs(const ParseArgs &) = delete;

	public:
		bool hasError() const;
		const std::string &getError() const;
		bool actionHasBeenDone() const;
		const std::string &getArg(const std::string &key);
		bool argExist(const std::string &key);

	private:
		void checkArgs();
		int findArg(const std::string &toFind);
		void help();

	private:
		int _nb;
		std::vector<std::string> _args;
		std::unordered_map<std::string, std::string> _content;
		bool _actionDone = false;
		std::string _error = "";
};

}