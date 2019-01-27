/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** ISocket
*/

#pragma once

#include <string>
#include "Net.hpp"

namespace net {
	class ISocket {
	public:
		ISocket() = default;
		virtual ~ISocket() = default;

	public:
		virtual bool connect(const std::string &ip, int port) = 0;
		virtual bool bind(int port = 0) = 0;
		virtual bool receive(net::ReceiveCallbackFn onReceiveCallback, void *data) = 0;
		virtual int send(const std::string &data) = 0;
		virtual int send(const char *data, size_t len) = 0;
	};
}