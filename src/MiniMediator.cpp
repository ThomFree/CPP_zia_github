/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** MiniMediator
*/

#include <iostream>
#include <string>
#include "MiniMediator.hpp"
#include "net/TCPSocket.hpp"
#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"
#include "DLLoader.hpp"

// Modules
#include "mods/BasicModule.hpp"
#include "mods/RequestDebuggerModule.hpp"
#include "mods/HelloWorldModule.hpp"
#include "mods/RequestParserModule.hpp"
#include "mods/ResponseMakerModule.hpp"

Zia::MiniMediator::MiniMediator(std::shared_ptr<Zia::net::TCPSocket> socket, Pizzia::IMapContainer *config) : _sock(socket), _config(config)
{
    std::cout << "[MEDIATOR] A new client has joined the server" << std::endl;
    _sock->receive([&](const char *data, size_t size, void *){
        this->readData(data, size);
    });
}

Zia::MiniMediator::~MiniMediator()
{
    std::cout << "[MEDIATOR] End of the client, destroying Mediator" << std::endl;
}

void Zia::MiniMediator::readData(const char *data, size_t size)
{
    std::cout << "[MEDIATOR] A new request has been received, starting modules..." << std::endl;
    std::string tmp(data, size);
    std::cout << "received : /" << tmp << "/" << std::endl;
    runModules(tmp);
}

void Zia::MiniMediator::runModules(std::string msg)
{
    std::cout << "[MEDIATOR] Starting modules..." << std::endl;
    Pizzia::HttpRequest req(msg);
    Pizzia::HttpResponse res;

    // BIEN SUR CE TRUC EST TEMPORAIRE ;)
    // Il faut ici mettre les modules a la suite
    //Pizzia::HelloWorldModule test;
    //test.run(req, res, _session, *_config);
    ////
    // Module 1 : BasicModule, return success
    ////
    //Pizzia::BasicModule test;
    //test.run(req, res, _session, *_config);

    ////
    // Module 2 : RequestParser, Parse la request a partir du getRaw et mets dans les variables de la request
    ////
    // Pizzia::RequestParserModule requestParser;
    // requestParser.run(req, res, _session, *_config);

    ////
    // Module 3 : HelloModule, creer une page HTTP qui contient le debug de la requete
    ////
    // Pizzia::RequestDebuggerModule test3;
    // test3.run(req, res, _session, *_config);

    Pizzia::DLLoader dl("../mods/HelloWorldModule.so");
    auto module = dl.getEntryPoint<Pizzia::moduleUPtr (*)()>("createHelloModule")();
    module->run(req, res, _session, *_config);

    ////
    // Module 4 : ResponseMakerModule, creer la reponse a partir du contenu des variables membres de la classe IResponse
    ////
    // Pizzia::ResponseMakerModule test4;
    // test4.run(req, res, _session, *_config);
    
    // Fin des modules
    std::cout << "[MEDIATOR]  End of the modules" << std::endl;
    _sock->send(res.getRaw());
}