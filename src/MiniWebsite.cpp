/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniWebsite
*/

#include <iostream>
#include "MiniWebsite.hpp"

Zia::MiniWebsite::MiniWebsite() : _netService(), _servSocket(_netService, false)
{
    if (_servSocket.bind(8080) && _servSocket.accept(
        [&](std::shared_ptr<Zia::net::TCPSocket> socket, void *data) {
            this->acceptClient(socket, data);
        }))
        std::cout << "[Website] Launched on port 8080" << std::endl;
    else
        throw std::runtime_error("Failed to start the website on port 8080");
}

Zia::MiniWebsite::~MiniWebsite()
{
    _clients.clear();
    _servSocket.disconnect();
    std::cout << "[Website] Stopped." << std::endl;
}

void Zia::MiniWebsite::run()
{
    _netService.run();
}

void Zia::MiniWebsite::acceptClient(std::shared_ptr<Zia::net::TCPSocket> socket, void *)
{
    std::cout << "[Website] A new client has just joined the server" << std::endl;
    addClient(socket);
}

void Zia::MiniWebsite::addClient(std::shared_ptr<Zia::net::TCPSocket> socket)
{
    MiniMediator *mediator = new MiniMediator(socket, &_config);
    _clients.push_back(mediator);
}