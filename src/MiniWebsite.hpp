/*
** EPITECH PROJECT, 2019
** $
** File description:
** MiniWebsite
*/

#include <vector>
#include <boost/asio/signal_set.hpp>
#include <memory>
#include "net/TCPSocket.hpp"
#include "net/NetworkService.hpp"
#include "http/MapContainer.hpp"
#include "MiniMediator.hpp"

#pragma once

namespace Zia {

class MiniWebsite {
	public:
		MiniWebsite();
		~MiniWebsite();
        MiniWebsite(const MiniWebsite &) = delete;
        MiniWebsite &operator=(const MiniWebsite &) = delete;

    public:
        void run();

	private:
        void acceptClient(std::shared_ptr<Zia::net::TCPSocket> socket, void *data);
        void addClient(std::shared_ptr<Zia::net::TCPSocket> socket);
        void stop();
    
    private:
        std::vector<MiniMediator *> _clients;
        net::NetworkService _netService;
        net::TCPSocket _servSocket;
        Pizzia::MapContainer _config;
};

}