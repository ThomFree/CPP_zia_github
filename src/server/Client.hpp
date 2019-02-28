/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <memory>

#include "net/TCPSocket.hpp"

#pragma once

namespace Zia {

class Client {
	public:
		explicit Client(net::TCPSocket &&socket);
		~Client() noexcept = default;
		Client() = delete;
		Client(const Client &) = delete;
		Client(Client &&) = default;
		Client &operator=(const Client &) = delete;
		Client &operator=(Client &&) = default;

	public:
		net::TCPSocket *socket() const;

	private:
		std::unique_ptr<net::TCPSocket> _socket;
};

}