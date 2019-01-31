//
// EPITECH PROJECT, 2018
// ZIA
// File description:
// sources
//

#include "ReadConsole.hpp"
#include <iostream>

ReadConsole::ReadConsole() : _state(console::ConsoleState::WAITING), _quitConsole(false)
{}

ReadConsole::~ReadConsole()
{}

void ReadConsole::readLoop()
{
  std::string cmdTemp;
  
  std::cout << "--- CONSOLE ---" << std::endl;
  while (!_quitConsole) {
    _mut.lock();
    std::cout << "> ";
    _state = console::ConsoleState::WAITING;
    _mut.unlock();
    std::getline(std::cin, cmdTemp);
    if (std::cin.eof()) {
      _mut.lock();
      _quitConsole = true;
      _mut.unlock();
      continue;
    } else
      addToQueue(cmdTemp);
  }
}

std::queue<std::string> ReadConsole::getQueueCmd() const
{
  return _cmdQueue;
}

const std::queue<std::string> &ReadConsole::copyQueueCmd() const
{
  return _cmdQueue;
}

void ReadConsole::addToQueue(const std::string &cmd)
{
  _mut.lock();
  _state = console::ConsoleState::READING;
  _cmdQueue.push(cmd);
  _mut.unlock();
}

void ReadConsole::displayQueue()
{
  std::queue<std::string> copy = copyQueueCmd();
  std::cout << std::endl << "--- Queue content ---" << std::endl;
  
  while (copy.size() > 0 ) {  
    std::cout << copy.front() << std::endl;
    copy.pop();
  }
  
}

int main(int ac, const char **av)
{
  ReadConsole console;

  console.readLoop();
  console.displayQueue();
  return 0;
}
