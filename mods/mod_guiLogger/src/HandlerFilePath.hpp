//
// EPITECH PROJECT, 2018
// Zia
// File description:
// HandlerFilePath
//

#pragma once
# include <iostream>
# include <experimental/filesystem>
# include <string>
# include "dems-api/Stage.hpp"
# include "dems-api/Config.hpp"

namespace GUILogger
{

namespace fs = std::experimental::filesystem;

class HandlerFilePath {

public:
	HandlerFilePath(const std::string &path) : _path(path) {};
	~HandlerFilePath() = default;
	std::string handleFilePath(dems::config::Config &config);

private:
	bool fileExists(const fs::path &path, const fs::path &sec_path);
	std::string getLastUser(const std::string &name);

private:
	std::string _path;
};

} // GUILogger