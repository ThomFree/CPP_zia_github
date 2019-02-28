/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#pragma once

#include <memory>

#include "net/TCPSocket.hpp"

namespace Zia {

class Client {
	public:
		explicit Client(net::TCPSocket &&socket);
		~Client() noexcept = default;
		Client(Client &&) = default;
		Client &operator=(const Client &) = delete;

		Client() = delete;
		Client(const Client &) = delete;
		Client &operator=(Client &&) = default;

	public:
		net::TCPSocket *socket() const;

	private:
		std::unique_ptr<net::TCPSocket> _socket;
};

}