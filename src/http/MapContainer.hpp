/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IMapContainer
*/

#include <unordered_map>
#include "api/IMapContainer.hpp"

#pragma once

namespace Pizzia {

class MapContainer : public IMapContainer {
	public:
		MapContainer() = default;
		~MapContainer() = default;
        MapContainer(const MapContainer &) = delete;
        MapContainer &operator=(const MapContainer &) = default;

    public:
        bool create(const std::string &key, const std::string &value) final;
        bool create(const std::string &key, int value) final;
        bool create(const std::string &key, bool value) final;
        bool create(const std::string &key, float value) final;

        void put(const std::string &key, const std::string &value) final;
        void put(const std::string &key, int value) final;
        void put(const std::string &key, bool value) final;
        void put(const std::string &key, float value) final;

        std::string getString(const std::string &key) const final;
        int getInt(const std::string &key) const final;
        bool getBool(const std::string &key) const final;
        float getFloat(const std::string &key) const final;

        void del(const std::string &key) final;
        bool has(const std::string &key) const final;

        std::unordered_map<std::string, std::string>::const_iterator begin() const final { return _data.begin(); }
        std::unordered_map<std::string, std::string>::const_iterator end() const final { return _data.end(); }

        private:
            std::unordered_map<std::string, std::string> _data;
};

}