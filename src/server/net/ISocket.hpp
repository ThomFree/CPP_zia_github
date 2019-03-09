/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** ISocket
*/

#include <cstddef>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#pragma once

namespace Zia::net {
constexpr size_t READ_SIZE = 1024;

class ISocket {
	public:
		virtual ~ISocket() = default;

	public:
		virtual bool connect(int, const std::string&) = 0;
		virtual void setReceive(const std::function<void(const char *, size_t)>&) = 0;
		virtual void setDisconnect(const std::function<void(ISocket*)>&) = 0;
		virtual void disconnect() = 0;
		virtual size_t send(const char *, size_t) = 0;
		virtual size_t send(const std::string&) = 0;

	private:
		virtual void handleReceive(const boost::system::error_code&, size_t) = 0;
		virtual void handleSend(const boost::system::error_code&) = 0;
};
}