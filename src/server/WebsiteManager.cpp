/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** WebsiteManager
*/

#include <iostream>
#include "WebsiteManager.hpp"

namespace Zia {

WebsiteManager::WebsiteManager(ParseArgs &parser) : _parser(parser)
{
    std::cout << "[Zia] Started." << std::endl;

    // DEBUG EXEMPLE D'UTILISATION DU PARSER
    // TODO remove those lines
    //if (_parser.argExist("-p"))
    //    std::cout << "PARSER :" << _parser.getArg("-p") << std::endl;
}

WebsiteManager::~WebsiteManager()
{
    std::cout << "[Zia] Stopped." << std::endl;
}

void WebsiteManager::launch()
{
}

}