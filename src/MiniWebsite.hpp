/*
** EPITECH PROJECT, 2019
** $
** File description:
** MiniWebsite
*/

#include <vector>
#include <boost/asio/signal_set.hpp>
#include "net/TCPSocket.hpp"
#include "net/NetworkService.hpp"
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
        void acceptClient(net::ISocket *socket, void *data);
        void addClient(net::ISocket *socket);
        void stop();
    
    private:
        std::vector<MiniMediator *> _clients;
        net::NetworkService _netService;
        net::TCPSocket _servSocket;
        boost::asio::signal_set _signals;
        // Ajouter la configuration du site ici sous la forme d'une key value
};

}