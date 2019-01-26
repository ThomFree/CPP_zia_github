/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniWebsite
*/

#include <iostream>
#include "MiniWebsite.hpp"

Pizzia::MiniWebsite::MiniWebsite()
{
}

Pizzia::MiniWebsite::~MiniWebsite()
{
}

void Pizzia::MiniWebsite::acceptClient()
{
    std::cout << "[Website] A new client has just joined the server" << std::endl;
    // Launch a new socket
    // Set the read callback to readData function
    // Start the listenning of the callback
    // Regoing into listen to accept mode
}