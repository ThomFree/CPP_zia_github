/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** Zia - main.cpp
*/

#include <iostream>
#include "http/MapContainer.hpp"

int main()
{
	Pizzia::MapContainer container;

	if (!container.add("string", std::string("ouioui")))
		return 84;
	container.add("int", 42);
	container.add("bool", 1);
	container.add("float", 42.4242f);

	std::cout << container.getString("string") << "/" << container.getInt("int") << "/" << container.getFloat("float") << "/" << container.getBool("bool") << std::endl;

	try {
		container.getString("unknown");
	} catch (...) {
		std::cout << "Success" << std::endl;
	}

	try {
		container.getBool("string");
	} catch (...) {
		std::cout << "Success" << std::endl;
	}

	container.add("string", std::string("nonnon"));
	if (container.getString("string") == "nonnon")
		std::cout << "failure" << std::endl;
	else
		std::cout << "Success" << std::endl;
	
	container.forceAdd("string", std::string("nonnon"));
	if (container.getString("string") == "nonnon")
		std::cout << "Success" << std::endl;
	else
		std::cout << "failure" << container.getString("string") << std::endl;
	return (0);
}