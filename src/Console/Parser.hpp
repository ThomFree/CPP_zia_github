//
// EPITECH PROJECT, 2018
// ZIA
// File description:
// header
//

#pragma once
# include <iostream>
# include <queue>
# include <algorithm>
# include <unordered_map>

class ParserCLI {
public:
  ParserCLI();
  ~ParserCLI() = default;
  void parseQueueCommand(std::queue<std::string> &cmds);

private:
  void parseStringCommand(const std::string &cmd);

  static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
  }

  static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
  }

  static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }

private:
  typedef void (*Commands)(const std::string &); // function pointer type
  typedef std::unordered_map<std::string, Commands> function_map;
  static void foo(const std::string &cmd);
  static void bar(const std::string &cmd);
  void resetCmd();
  
private:
  function_map _fmap;
  std::vector<std::string> _tokens;

};