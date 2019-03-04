/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPClient
*/

#pragma once

#include <memory>

#include "net/TCPSocket.hpp"

namespace Zia::net {

class TCPClient {
	public:
		explicit TCPClient(net::TCPSocket &&socket);
		~TCPClient() noexcept = default;
		TCPClient(TCPClient &&) = default;
		TCPClient &operator=(const TCPClient &) = delete;

		TCPClient() = delete;
		TCPClient(const TCPClient &) = delete;
		TCPClient &operator=(TCPClient &&) = default;

	public:
		net::TCPSocket *socket() const;

	private:
		std::unique_ptr<net::TCPSocket> _socket;
};

}