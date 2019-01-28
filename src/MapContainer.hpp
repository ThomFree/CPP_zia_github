/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IMapContainer
*/

#include <unordered_map>
#include "IMapContainer.hpp"

#pragma once

namespace Pizzia {

class MapContainer : IMapContainer {
	public:
		MapContainer() = default;
		~MapContainer() = default;
        MapContainer(const MapContainer &) = delete;
        MapContainer &operator=(const MapContainer &) = delete;

    public:
        bool add(const std::string &key, const std::string &value) final;
        bool add(const std::string &key, int value) final;
        bool add(const std::string &key, bool value) final;
        bool add(const std::string &key, float value) final;

        bool edit(const std::string &key, const std::string &value) final;
        bool edit(const std::string &key, int value) final;
        bool edit(const std::string &key, bool value) final;
        bool edit(const std::string &key, float value) final;

        void forceAdd(const std::string &key, const std::string &value) final;
        void forceAdd(const std::string &key, int value) final;
        void forceAdd(const std::string &key, bool value) final;
        void forceAdd(const std::string &key, float value) final;

        std::string getString(const std::string &key) const final;
        int getInt(const std::string &key) const final;
        bool getBool(const std::string &key) const final;
        float getFloat(const std::string &key) const final;

        void del(const std::string &key) final;
        // TODO
        // Est-ce qu'on mettrait pas les iterateurs begin et end pour par exemple 
        // pouvoir faire un logger de la map en iterant avec le begin et le end

        private:
            std::unordered_map<std::string, std::string> _data;
};

}