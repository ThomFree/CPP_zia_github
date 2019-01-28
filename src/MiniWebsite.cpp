/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniWebsite
*/

#include <iostream>
#include "MiniWebsite.hpp"

Pizzia::MiniWebsite::MiniWebsite() : _netService(), _servSocket(_netService), _signals(_netService, SIGINT)
{
    if (_servSocket.bind(8080) && _servSocket.accept(
        [&](net::ISocket *socket, void *data) {
            this->acceptClient(socket, data);
        }))
        std::cout << "[Website] Launched on port 8080" << std::endl;
    else
        throw std::runtime_error("Failed to start the website on port 8080");
    _signals.async_wait(
        [&](const boost::system::error_code &, int) {
            this->stop();
        });
}

Pizzia::MiniWebsite::~MiniWebsite()
{
    _clients.clear();
    std::cout << "[Website] Stopped." << std::endl;
}

void Pizzia::MiniWebsite::stop()
{
    for (MiniMediator *mediator : _clients) {
        mediator->stop();      
    }
    _servSocket.disconnect();
    _netService.stop();
}

void Pizzia::MiniWebsite::run()
{
    _netService.run();
}

void Pizzia::MiniWebsite::acceptClient(net::ISocket *socket, void *)
{
    std::cout << "[Website] A new client has just joined the server" << std::endl;
    addClient(socket);
    // Set the read callback to readData function
    // Start the listenning of the callback
    // Regoing into listen to accept mode
}

// TODO Transmettre ici la configuration du site au MiniMediator
// Dans la version future il faut proteger contre le multi thread exriture
void Pizzia::MiniWebsite::addClient(net::ISocket *sock)
{
    MiniMediator *mediator = new MiniMediator(sock);
    _clients.push_back(mediator);
}