#include <iostream>

#include "NetworkService.hpp"
#include "TCPAcceptor.hpp"
#include "TCPSocket.hpp"
#include "SSLSocket.hpp"
#include "TCPClient.hpp"

/*
 * When a TCPClient is disco. Isn't necessary
 */
static void disconnectCallback(Zia::net::ISocket *socket)
{
	std::cout << "[ TCPClient disconnected { " << socket << "} ]" << std::endl;
}

/*
 * Connect Callback
 */
static void connectCallBack(std::shared_ptr<Zia::net::TCPClient> TCPClient)
{
	std::cout << "[ Accepted new TCPClient ]" << std::endl;
	Zia::net::TCPSocket *socket = static_cast<Zia::net::TCPSocket*>(TCPClient->socket());

	socket->setDisconnect([socket](Zia::net::ISocket *socket) { disconnectCallback(socket); });
	socket->setReceive([](const char *data, size_t size) {
		((char*)data)[size - 1] = '\0';
		std::cout << "{Received data: { " << data << " } ]" << std::endl;
	});
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
	std::vector<std::shared_ptr<Zia::net::TCPClient>> list; // TCPClient List (Website manager)

	if (acceptor.bind(8080))
		acceptor.accept<Zia::net::TCPSocket>([&list](std::shared_ptr<Zia::net::TCPClient> TCPClient) -> void { list.push_back(TCPClient); connectCallBack(TCPClient); });
	else
		std::cerr << "[ Error while binding socket on port. ]" << std::endl;

	if (acceptor.bind(4343))
		acceptor.accept<Zia::net::SSLSocket>([&list](std::shared_ptr<Zia::net::TCPClient> TCPClient) -> void { list.push_back(TCPClient); connectCallBack(TCPClient); });
	else
		std::cerr << "[ Error while binding socket on port. ]" << std::endl;

	netService.run();
	return 0;
}