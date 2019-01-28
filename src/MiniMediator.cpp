/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniMediator
*/

#include <iostream>
#include <string>
#include "MiniMediator.hpp"
#include "net/TCPSocket.hpp"

// TODO recevoir la conf du website en plus du socket
Pizzia::MiniMediator::MiniMediator(net::ISocket *sock) : _sock((net::TCPSocket *)sock)
{
    std::cout << "[MEDIATOR] A new request was received" << std::endl;
    // Set le disconnect ici mais jai pas prevu l'archi pour pour le mini zia
}

Pizzia::MiniMediator::~MiniMediator()
{
    std::cout << "[MEDIATOR] End of the request, destroying Mediator" << std::endl;
    _sock->disconnect();
    delete _sock;
}

void Pizzia::MiniMediator::readData()
{
    // Ici on read les data du socket
    // On envoie les datas a run module
    runModules();
    // On se remet en read waiting
}

void Pizzia::MiniMediator::runModules()
{
    // Ici on construit une request
    // Ici on construit une reponse

    // For loop pour iterer sur tous les modules
}

void Pizzia::MiniMediator::stop()
{
    _sock->disconnect();
}