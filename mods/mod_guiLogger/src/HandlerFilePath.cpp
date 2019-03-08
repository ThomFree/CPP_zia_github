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
  std::cout << "Je compare : " << path << " -/- " << sec_path << std::endl;
  return path == sec_path;
}

std::string HandlerFilePath::getLastUser(const std::string &defaultName)
{
  std::string defaultUser = defaultName;
  uint8_t id = 1;
  std::string nameFile = _path + defaultName + std::to_string(id) + ".log";
  std::ifstream file(nameFile);

  if (!(_path.back() == '/')) {
    std::cout << "file renseigné : " << _path << std::endl;
    return _path;
  }
  
  while (!file.fail()) {
    file.close();
    id++;
    nameFile = _path + defaultName + std::to_string(id) + ".log";
    file.open(nameFile);
  }
  file.close();
  return nameFile;
}

std::string HandlerFilePath::handleFilePath(dems::config::Config &config)
{
  std::string fileName;
  auto modules = std::get<dems::config::ConfigObject>(config["modules"].v);
  auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
  std::size_t found = _path.find_last_of("/");
  std::string lastDir = _path.substr(0,found);

  std::experimental::filesystem::create_directories(lastDir);
  fileName = getLastUser(std::get<std::string>(config["name"].v));
  _path = fileName;
  return fileName;
}

} // GUILogger
