/*
** EPITECH PROJECT, 2018
** CPP_zia_github
** File description:
** DLLoader
*/

#include "DLLoader.hpp"
#include <dlfcn.h>
#include <iostream>

Pizzia::DLLoader::DLLoader(const std::string &name) : _nameMod(name)
{
	_handle = dlopen(_nameMod.c_str(), RTLD_NOW);
	std::cerr << dlerror() << std::endl;
	if (_handle == NULL)
		throw std::runtime_error("Invalid module name");
}

Pizzia::DLLoader::~DLLoader()
{
	dlclose(_handle);
}