/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** MapContainer
*/

#include "MapContainer.hpp"

MapContainer::MapContainer()
{
}

MapContainer::~MapContainer()
{
}

bool MapContainer::add(const std::string &key, const std::string &value)
{
    auto it = _map.emplace(key, value);

    return (it.second);
}

void MapContainer::del(const std::string &key)
{
    _map.erase(key);
}

bool MapContainer::edit(const std::string &key, const std::string &value)
{
    auto it = _map.find(key);

    if (it == _map.end()) {
        return (false);
    } else {
        it->second = value;
        return (true);
    }
}