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
Zia::MiniMediator::MiniMediator(net::ISocket *sock) : _sock((net::TCPSocket *)sock)
{
    std::cout << "[MEDIATOR] A new client has joined the server" << std::endl;
    // Set le callback du read et le start
    // Set le disconnect
}

Zia::MiniMediator::~MiniMediator()
{
    std::cout << "[MEDIATOR] End of the client, destroying Mediator" << std::endl;
    _sock->disconnect();
    delete _sock;
}

void Zia::MiniMediator::readData()
{
    std::cout << "[MEDIATOR] A new request has been received, starting modules..." << std::endl;
    // Ici on read les data du socket
    // On envoie les datas a run module
    runModules();
    // On se remet en read waiting
}

void Zia::MiniMediator::runModules()
{
    // Ici on construit une request
    // Ici on construit une reponse
    // On set le rawData au contenu du msg recu

    // For loop pour iterer sur tous les modules
}

void Zia::MiniMediator::stop()
{
    _sock->disconnect();
}