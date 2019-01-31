//
// EPITECH PROJECT, 2018
// ZIA
// File description:
// sources
//

#include "Parser.hpp"
#include <sstream>
#include <vector>

ParserCLI::ParserCLI()
{
  // Basic Commands
  _fmap.emplace("create", &foo);
  _fmap.emplace("enter", &foo);
  _fmap.emplace("back", &bar);
  _fmap.emplace("list", &bar);
  _fmap.emplace("stop", &bar);
  _fmap.emplace("help", &bar);

  // Web Commands
  _fmap.emplace("delete", &foo);
  _fmap.emplace("start", &bar);
  _fmap.emplace("pause", &bar);
  _fmap.emplace("status", &foo);

  // Module Commands
  _fmap.emplace("enable", &bar);
  _fmap.emplace("disable", &foo);
  _fmap.emplace("reload", &foo);

  _fmap.emplace("reload_all", foo);
}

void ParserCLI::foo(const std::string &cmd)
{
  std::cout << "foo" << std::endl;
}

void ParserCLI::bar(const std::string &cmd)
{
  std::cout << "bar" << std::endl;
}

void ParserCLI::parseQueueCommand(std::queue<std::string> &cmds)
{
  if (cmds.size() > 0) {
    std::string temp = cmds.front();
    cmds.pop();
    parseStringCommand(temp);

    auto iter = _fmap.find(_tokens[0]);
    if (iter == _fmap.end()) {
        std::cerr << "Not a function. \"help\" to display the command list." << std::endl;
    }
    (*iter->second)(_tokens[0]);
    resetCmd();
    
  } else
    return;
}

void ParserCLI::parseStringCommand(const std::string &cmd)
{
  std::string temp = cmd;
  std::string token;
  std::string delimiter = " ";
  size_t pos = 0;

  trim(temp);
  while ((pos = temp.find(delimiter)) != std::string::npos) {
    token = temp.substr(0, pos);
    if (!(token == " ")) {
      _tokens.push_back(token);
    }
    temp.erase(0, pos + delimiter.length());
  }
  _tokens.push_back(temp);
}

void ParserCLI::resetCmd()
{
  _tokens.clear();
}

int main()
{
  std::string cmdTemp;
  ParserCLI oui;
  std::queue<std::string> q;

  while (42) {
    std::getline(std::cin, cmdTemp);
    if (std::cin.eof()) {
      std::cout << "END" << std::endl;
      return 21;
    }
    q.push(cmdTemp);
    oui.parseQueueCommand(q);
  }
  return 0;
}