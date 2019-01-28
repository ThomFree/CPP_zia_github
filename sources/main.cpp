/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** main
*/

#include <iostream>
#include "net/TCPSocket.hpp"
#include "net/NetworkService.hpp"

static void receiveCallback(net::TCPSocket *socket, const char *data, size_t size)
{
    std::cout << "[ Data received of size: " << size << " - content: " << data << "]" << std::endl;
}

static void disconnectCallback(net::ISocket *socket)
{
    std::cout << "[ Client disconnected ]" << std::endl;
}

static void connectCallBack(net::ISocket *socket)
{
    std::cout << "[ Accepted new client ]" << std::endl;
    ((net::TCPSocket*)socket)->onDisconnect([&](net::ISocket *socket, void*) { disconnectCallback(socket); });
    ((net::TCPSocket*)socket)->receive([&](const char *data, size_t size, void *isocket) {
                                receiveCallback((net::TCPSocket*)isocket, data, size);}, socket);
}

int main(int, char *[])
{
    net::NetworkService netService;

    net::TCPSocket sock(netService);
    if (sock.bind(8080))
        sock.accept([&](net::ISocket *socket, void*){ connectCallBack(socket); });
    else
        std::cerr << "[ Error while binding socket on port. ]" << std::endl;
    netService.run();
    return 0;
}
