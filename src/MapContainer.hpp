/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** MapContainer
*/

#pragma once

#include <unordered_map>
#include <string>

class MapContainer {
	public:
		MapContainer();
		~MapContainer();

        bool add(const std::string &key, const std::string &value);
        void del(const std::string &key);
        bool edit(const std::string &key, const std::string &value);

        std::string operator[](const std::string &key) { return _map[key]; }
        int size() { return _map.size(); }

	private:
        std::unordered_map<std::string, std::string> _map;
};
