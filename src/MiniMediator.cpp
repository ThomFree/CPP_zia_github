/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniMediator
*/

#include <iostream>
#include <string>
#include "MiniMediator.hpp"

Pizzia::MiniMediator::MiniMediator() // TODO envoyer la conf du site au mediator (en référence comme ca on peut la changer en live)
{
    std::cout << "[MEDIATOR] A new request was received" << std::endl;
}

Pizzia::MiniMediator::~MiniMediator()
{
    std::cout << "[MEDIATOR] End of the request, destroying Mediator" << std::endl;
}

void Pizzia::MiniMediator::readData()
{
    // Ici on read les data du socket
    // On envoie les datas a run module
    runModules();
    // On se remet en read wainting
}

void Pizzia::MiniMediator::runModules()
{
    // Ici on construit une request
    // Ici on construit une reponse

    // For loop pour iterer sur tous les modules
}