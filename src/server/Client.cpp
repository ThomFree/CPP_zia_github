/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include "Client.hpp"

namespace Zia {

Client::Client(std::shared_ptr<net::TCPSocket> &sock) : _tcpSocket(sock)
{
}

Client::~Client()
{
}

}