/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** ParseArgs
*/

#include <iostream>
#include "ParseArgs.hpp"

namespace Zia {

ParseArgs::ParseArgs(int ac, const char * const av[]) : _nb(ac)
{
    for (int i = 0; i < _nb; i++) {
        _args.push_back(av[i]);
    }
    checkArgs();
}

bool ParseArgs::actionHasBeenDone() const
{
    return _actionDone;
}

bool ParseArgs::hasError() const
{
    return _error == "" ? 0 : 1;
}

const std::string &ParseArgs::getError() const
{
    return _error;
}

bool ParseArgs::argExist(const std::string &key)
{
    if (_content.find(key) != _content.end())
        return true;
    return false;
}

const std::string &ParseArgs::getArg(const std::string &key)
{
    return _content.at(key);
}

void ParseArgs::checkArgs()
{
    if (findArg("-h") > -1) {
        help();
        return;
    }
    if (findArg("-p") > -1 && findArg("-p") + 1 < _nb) {
        _content["-p"] = _args[findArg("-p") + 1];
        return;
    }
}

int ParseArgs::findArg(const std::string &toFind)
{
    for (unsigned int i = 0; i < _args.size(); i++)
        if (_args[i] == toFind)
            return i;
    return -1;
}

void ParseArgs::help()
{
    _actionDone = true;
    std::cout << "Usage : ./zia [-p PATH_TO_WEBSITE_CONFIG] [-h]" << std::endl;
}

}