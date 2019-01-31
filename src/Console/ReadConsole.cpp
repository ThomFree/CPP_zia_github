//
// EPITECH PROJECT, 2018
// ReadConsole
// File description:
// sources
//

#include "ReadConsole.hpp"
#include <iostream>
#include <mutex>

std::mutex G_CONSOLE_MUTEX;

ReadConsole::ReadConsole() : _state(console::ConsoleState::WAITING), _quitConsole(false)
{}

ReadConsole::~ReadConsole()
{}

void ReadConsole::readLoop()
{
  std::string cmdTemp;
  
  std::cout << "--- CONSOLE ---" << std::endl;
  while (!_quitConsole) {
    G_CONSOLE_MUTEX.lock();
    std::cout << "> ";
    _state = console::ConsoleState::WAITING;
    G_CONSOLE_MUTEX.unlock();
    std::getline(std::cin, cmdTemp);
    if (std::cin.eof()) {
      G_CONSOLE_MUTEX.lock();
      _quitConsole = true;
      G_CONSOLE_MUTEX.unlock();
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
  G_CONSOLE_MUTEX.lock();
  _state = console::ConsoleState::READING;
  _cmdQueue.push(cmd);
  G_CONSOLE_MUTEX.unlock();
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
