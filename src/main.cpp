/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** main
*/

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include "TCPAcceptor.hpp"

/*
 * When a new payload is recv
 */
static void receiveCallback(const char *data, size_t size)
{
    std::cout << "[ Data received of size: " << size << " - content: " << data << "]" << std::endl;
}

/*
 * When a client is disco. Isn't necessary
 */
static void disconnectCallback(Zia::net::TCPSocket *socket)
{
    std::cout << "[ Client disconnected { " << socket << "} ]" << std::endl;
}

/*
 * Connect Callback
 */
static void connectCallBack(std::shared_ptr<Zia::net::Client> client)
{
    std::cout << "[ Accepted new client ]" << std::endl;
    Zia::net::TCPSocket *socket = client->socket();

    socket->setDisconnect([socket](Zia::net::TCPSocket *socket) { disconnectCallback(socket); });
    socket->setReceive([](const char *data, size_t size) { receiveCallback(data, size); });
}

/*
 * When SIGINT is catched
 */
static void stopCbFn()
{
    std::cout << "Network service callback Fn" << std::endl;
}

int main(int, char *[])
{
    Zia::net::NetworkService netService(&stopCbFn);
    Zia::net::TCPAcceptor acceptor(netService); // Acceptor (Website manager)
    std::vector<std::shared_ptr<Zia::net::Client>> list; // Client List (Website manager)

    if (acceptor.bind(8080))
        acceptor.accept([&list](std::shared_ptr<Zia::net::Client> client) -> void { list.push_back(client); connectCallBack(client); });
    else
        std::cerr << "[ Error while binding socket on port. ]" << std::endl;

    netService.run();
    return 0;
}