/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniMediator
*/

#include <vector>
#include "api/IModule.hpp"
#include "net/TCPSocket.hpp"

#pragma once

namespace Pizzia {

class MiniMediator {
	public:
		MiniMediator() = delete;
        MiniMediator(net::ISocket *sock);
		~MiniMediator();
        MiniMediator(const MiniMediator &) = delete;
        MiniMediator &operator=(const MiniMediator &) = delete;

	public:
        void runModules(); // TODO
        void stop();

    private:
        void readData(); // TODO
    
    private:
        net::TCPSocket *_sock;
        std::vector<IModule> _modules;
};

}