/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniMediator
*/

#include <iostream>
#include <string>
#include "MiniMediator.hpp"

MiniMediator::MiniMediator()
{
    std::cout << "[MEDIATOR] A new request was received" << std::endl;
}

MiniMediator::~MiniMediator()
{
    std::cout << "[MEDIATOR] End of the request, destroying Mediator" << std::endl;
}

void MiniMediator::runModules()
{
}