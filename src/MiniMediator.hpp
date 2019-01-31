/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniMediator
*/

#include <vector>
#include "api/IModule.hpp"
#include "net/TCPSocket.hpp"
#include "api/IMapContainer.hpp"
#include "http/MapContainer.hpp"

#pragma once

namespace Zia {

class MiniMediator {
	public:
		MiniMediator() = delete;
        MiniMediator(std::shared_ptr<Zia::net::TCPSocket> socket, Pizzia::IMapContainer *config);
		~MiniMediator();
        MiniMediator(const MiniMediator &) = delete;
        MiniMediator &operator=(const MiniMediator &) = delete;

	public:
        void runModules();

    private:
        void readData(const char *data, size_t size);
    
    private:
        std::shared_ptr<Zia::net::TCPSocket> _sock;
        Pizzia::IMapContainer *_config;
        Pizzia::MapContainer _session;
};

}