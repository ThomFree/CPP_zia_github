/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#pragma once
#include <memory>

#include "TCPSocket.hpp"

namespace Zia {
	namespace net {
		class Client {
			public:
				explicit Client(TCPSocket &&socket);
				~Client() noexcept = default;
				Client() = delete;
				Client(const Client &) = delete;
				Client(Client &&) = default;
				Client &operator=(const Client &) = delete;
				Client &operator=(Client &&) = default;

			/*
			 * Methods
			 */
			public:
				TCPSocket *socket() const;

			/*
			 * Fields
			 */
			private:
				std::unique_ptr<TCPSocket> _socket;

		};
	}
}