/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniWebsite
*/

#include <iostream>
#include "MiniWebsite.hpp"

MiniWebsite::MiniWebsite()
{
}

MiniWebsite::~MiniWebsite()
{
}

void MiniWebsite::acceptClient()
{
    std::cout << "[Website] A new client has just joined the server" << std::endl;
    // Launch a new socket
    // Set the read callback to readContent function
    // Start the listenning of the callback
}