/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** Net
*/

#pragma once

#include <boost/asio.hpp>

namespace net {
	std::string getMyIP() noexcept;
	class ISocket;

	using ReceiveCallbackFn = std::function<void (const char *, int, void *)>;
	using ConnectCallbackFn = std::function<void (ISocket *, void *)>;
	using RawSocket = boost::asio::ip::tcp::socket;

	static constexpr char google_dns_server[] = "8.8.8.8";
	static constexpr char localhost[] = "127.0.0.1";
	static constexpr size_t read_size = 1024;
}
