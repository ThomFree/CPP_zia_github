/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPAcceptor
*/

#pragma once
#include <boost/asio.hpp>
#include <functional>
#include <memory>

#include "NetworkService.hpp"
#include "Client.hpp"

namespace Zia {
	static constexpr size_t READ_SIZE = 1024;

	class Client;

	namespace net {
		class TCPAcceptor {
			using acceptCallback_t = std::function<void(std::shared_ptr<Client>)>;
			public:
				explicit TCPAcceptor(NetworkService &netService);
				~TCPAcceptor() noexcept = default;
				TCPAcceptor() = delete;
				TCPAcceptor(const TCPAcceptor &) = delete;
				TCPAcceptor(TCPAcceptor &&) = default;
				TCPAcceptor &operator=(const TCPAcceptor &) = delete;
				TCPAcceptor &operator=(TCPAcceptor &&) = default;

			/*
			 * Methods
			 */
			public:
				bool accept(acceptCallback_t &&callback);
				bool bind(int port);

			/*
			 * Fields
			 */
			private:
				NetworkService &_netService;
				boost::asio::ip::tcp::acceptor _acceptor;
		};
	}
}
