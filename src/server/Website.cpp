/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Website
*/

#include <iostream>
#include "Website.hpp"

namespace Zia {

Website::Website(const std::string &filename) : _filename(filename), _conf() //, Parser(filename)
{
	// set default value here or use those in the config file
	// instantiate all the modules from the file
	// if everything is good start to accept connection
	std::cout << "\t[Website - " + _filename + "] Started." << std::endl;
}

Website::~Website()
{
	std::cout << "\t[Website - " + _filename + "] Stopped." << std::endl;
}

}