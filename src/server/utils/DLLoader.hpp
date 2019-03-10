/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** load dynamic lib
*/

#include <iostream>
#include <memory>

#pragma once

namespace Zia {

#ifdef _WIN32
	#include <windows.h>
	class DLLoader {
		public:
			DLLoader(const std::string &mod);
			~DLLoader();
			void *getHandle() const { return _handle; }

			template <typename T>
			T getEntryPoint(const std::string &name)
			{
				T func;
				func = reinterpret_cast<T>(GetProcAddress((HMODULE)_handle, name.c_str()));
				return (func);
			}

		private:
			const std::string _nameMod;
			void *_handle;
	};
#elif __linux__
	#include <dlfcn.h>
	class DLLoader {
		public:
			DLLoader(const std::string &mod);
			~DLLoader();
			void *getHandle() const { return _handle; }

			template <typename T>
			T getEntryPoint(const std::string &name)
			{
				T func;
				func = reinterpret_cast<T>(dlsym(_handle, name.c_str()));
				return (func);
			}

		private:
			const std::string _nameMod;
			void *_handle;
	};
#endif
}