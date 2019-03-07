//
// EPITECH PROJECT, 2018
// Zia
// File description:
// sources
//

#include <fstream>
#include "HandlerFilePath.hpp"

namespace GUILogger
{

namespace fs = std::experimental::filesystem;

bool HandlerFilePath::fileExists(const fs::path &path, const fs::path &sec_path)
{
  return path == sec_path;
}

std::string HandlerFilePath::getLastUser()
{
  std::string defaultUser = "user";
  std::string finalUser = "";
  bool isEmpty = true;
  fs::path p;
  uint8_t id = 1;

  for (auto it = fs::directory_iterator(_path); it != fs::directory_iterator(); it++) {
    isEmpty = false;
    p = fs::path(_path + defaultUser + std::to_string(id) + ".log");
    if (fileExists(p, *it)) {
      id++;
      finalUser = _path + defaultUser + std::to_string(id) + ".log";
    }
    std::cout << "rentré dans le for" << std::endl;
  }
  if (isEmpty)
    finalUser = _path + defaultUser + std::to_string(id) + ".log";
  return finalUser;
}

std::string HandlerFilePath::handleFilePath(dems::Context &ctx)
{
  if (ctx.config.find("logPath") == ctx.config.end()) {
			std::experimental::filesystem::create_directories(_path);

			_path = getLastUser();
			ctx.config["logPath"].v = _path;
			std::cout << "Path required. Creating logs in " << _path << std::endl;

		}	else
			_path = std::get<std::string>(ctx.config["logPath"].v);

  return _path;
}

} // GUILogger
