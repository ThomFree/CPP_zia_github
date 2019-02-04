/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** load dynamic lib
*/

#include <dlfcn.h>
#include <iostream>

#pragma once
# include "api/IModule.hpp"

namespace Pizzia {
class DLLoader {
	public:
		DLLoader(const std::string &mod);
		~DLLoader();
		void *getHandle() const { return _handle; }
		void loadMod(const std::string &mod);

		template <typename T>
		T getEntryPoint(const std::string &name)
		{
			T func;
			std::cout << "Entry point" << std::endl;
			func = reinterpret_cast<T>(dlsym(_handle, name.c_str()));
			return (func);
		}

	private:
		const std::string _nameMod;
		void *_handle;
};
}