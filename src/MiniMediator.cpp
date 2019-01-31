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

// Modules
#include "mods/BasicModule.hpp"

Zia::MiniMediator::MiniMediator(std::shared_ptr<Zia::net::TCPSocket> socket, Pizzia::IMapContainer *config) : _sock(socket), _config(config)
{
    std::cout << "[MEDIATOR] A new client has joined the server" << std::endl;
    _sock->receive([&](const char *data, size_t size, void *){
        this->readData(data, size);
    });
}

Zia::MiniMediator::~MiniMediator()
{
    std::cout << "[MEDIATOR] End of the client, destroying Mediator" << std::endl;
}

void Zia::MiniMediator::readData(const char *data, size_t size)
{
    std::cout << "[MEDIATOR] A new request has been received, starting modules..." << std::endl;
    std::string tmp(data, size);
    std::cout << "received : /" << tmp << "/" << std::endl;
    runModules();
}

void Zia::MiniMediator::runModules()
{
    std::cout << "[MEDIATOR] Starting modules..." << std::endl;
    // TODO
    // Ici on construit une request
    // Ici on construit une reponse
    // (IMapContainer *)&_session, *_config
    // On set le rawData au contenu du msg recu

    // BIEN SUR CE TRUC EST TEMPORAIRE ;)
    // Pizzia::BasicModule test;
    // test.run(/* */);
    // std::cout << "[MEDIATOR]  End of the modules" << std::endl;
}