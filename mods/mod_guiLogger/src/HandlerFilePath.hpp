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

namespace GUILogger
{

namespace fs = std::experimental::filesystem;

class HandlerFilePath {

public:
	HandlerFilePath(const std::string &path) : _path(path) {};
	~HandlerFilePath() = default;
	std::string handleFilePath(dems::Context &ctx);

private:
	bool fileExists(const fs::path &path, const fs::path &sec_path);
	std::string getLastUser();

private:
	std::string _path;
};

} // GUILogger