/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** MapContainer
*/

// TODO remove this include
#include <iostream>
#include "MapContainer.hpp"

bool Pizzia::MapContainer::create(const std::string &key, const std::string &value)
{
    const auto &it =  _data.emplace(key, value);

    return it.second;
}

bool Pizzia::MapContainer::create(const std::string &key, int value)
{
    const auto &it =  _data.emplace(key, std::to_string(value));

    return it.second;
}

bool Pizzia::MapContainer::create(const std::string &key, bool value)
{
    const auto &it =  _data.emplace(key, std::to_string(value));

    return it.second;
}

bool Pizzia::MapContainer::create(const std::string &key, float value)
{
    const auto &it =  _data.emplace(key, std::to_string(value));

    return it.second;
}

void Pizzia::MapContainer::put(const std::string &key, const std::string &value)
{
    _data[key] = value;
}

void Pizzia::MapContainer::put(const std::string &key, int value)
{
    _data[key] = std::to_string(value);
}

void Pizzia::MapContainer::put(const std::string &key, bool value)
{
    _data[key] = std::to_string(value);
}

void Pizzia::MapContainer::put(const std::string &key, float value)
{
    _data[key] = std::to_string(value);
}

std::string Pizzia::MapContainer::getString(const std::string &key) const
{
    return _data.at(key);
}

int Pizzia::MapContainer::getInt(const std::string &key) const
{
    return std::stoi(_data.at(key));
}

bool Pizzia::MapContainer::getBool(const std::string &key) const
{
    if (_data.at(key) == "1")
        return 1;
    else if (_data.at(key) == "0")
        return 0;
    throw std::invalid_argument("Your boolean was invalid");
}

float Pizzia::MapContainer::getFloat(const std::string &key) const
{
    return std::stof(_data.at(key));
}

void Pizzia::MapContainer::del(const std::string &key)
{
     _data.erase(key);
}

bool Pizzia::MapContainer::has(const std::string &key) const
{
    return (_data.find(key) ==  _data.end()) ? false : true; 
}