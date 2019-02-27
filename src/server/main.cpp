/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** main
*/

#include <iostream>
#include "net/TCPSocket.hpp"
#include "net/NetworkService.hpp"

static void receiveCallback(const char *data, size_t size)
{
	std::cout << "[ Data received of size: " << size << " - content: " << data << "]" << std::endl;
}

static void disconnectCallback(Zia::net::TCPSocket *socket)
{
	std::cout << "[ Client disconnected ]" << std::endl;
}

static void connectCallBack(std::shared_ptr<Zia::net::TCPSocket>/*Zia::net::TCPSocket **/socket)
{
	std::cout << "[ Accepted new client ]" << std::endl;
	socket->onDisconnect([socket](Zia::net::TCPSocket *socket, void*) { disconnectCallback(socket); });
	socket->receive([&](const char *data, size_t size, void*) {
								receiveCallback(data, size);});
}

static void stopCbFn()
{
	std::cout << "Network service callback Fn" << std::endl;
}

int main()
{
	std::cout << "Hello world!" << std::endl;

	Zia::net::NetworkService netService(&stopCbFn);
	Zia::net::TCPSocket sock(netService, true);
	if (sock.bind(8080))
		sock.accept([&sock](std::shared_ptr<Zia::net::TCPSocket> /*net::TCPSocket **/socket, void*)
		{ connectCallBack(socket); });
	else
		std::cerr << "[ Error while binding socket on port. ]" << std::endl;
	netService.run();
	sock.disconnect();
	return 0;
}