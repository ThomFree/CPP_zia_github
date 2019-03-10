/*
** EPITECH PROJECT, 2018
** CPP_zia_github
** File description:
** DLLoader
*/

#include "DLLoader.hpp"
#include <iostream>

namespace Zia {
	#ifdef _WIN32
		DLLoader::DLLoader(const std::string &name) : _nameMod(name)
		{
			_handle = LoadLibraryA(_nameMod.c_str());
			if (_handle == NULL)
				throw std::runtime_error("Invalid module name");
		}

		DLLoader::~DLLoader()
		{
			FreeLibrary((HMODULE)(_handle));
		}
	#elif __linux__
		DLLoader::DLLoader(const std::string &name) : _nameMod(name)
		{
			_handle = dlopen(_nameMod.c_str(), RTLD_NOW);
			std::cerr << dlerror() << std::endl;
			if (_handle == NULL)
				throw std::runtime_error("Invalid module name");
		}

		DLLoader::~DLLoader()
		{
			dlclose(_handle);
		}
	#endif
}