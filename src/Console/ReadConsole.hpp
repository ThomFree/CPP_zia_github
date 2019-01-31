//
// EPITECH PROJECT, 2018
// READCONSOLE_HPP_
// File description:
// header
//

#pragma once
# include <iostream>
# include <queue>
// # include "Parser.hpp"

namespace console {
	enum ConsoleState {
		READING,
		WAITING
	};
}

class ReadConsole {
public:
	ReadConsole();
	~ReadConsole();

	void readLoop();
	std::queue<std::string> getQueueCmd() const;
	void addToQueue(const std::string &cmd);
	const std::queue<std::string> &copyQueueCmd() const;
	void displayQueue();

private:
	console::ConsoleState _state;
	bool _quitConsole;
	std::string _cmd;
	// Parser _parser;
	std::queue<std::string> _cmdQueue;
};
