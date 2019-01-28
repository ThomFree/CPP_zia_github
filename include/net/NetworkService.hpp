/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** NetworkService
*/

#pragma once

namespace net {
	class NetworkService : public boost::asio::io_service {
	public:
		NetworkService() : boost::asio::io_service() {}
		~NetworkService() = default;

	public:
		inline void run() { boost::asio::io_service::run(); }

		inline void stop() { boost::asio::io_service::stop(); }
	};
}