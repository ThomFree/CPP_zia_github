//
// EPITECH PROJECT, 2018
// Zia
// File description:
// 2JsonParser
//

#pragma once
# include <iostream>
# include <fstream>
# include <string>
# include <nlohmann/json.hpp>
# include "dems-api/Config.hpp"

namespace Zia {

class JsonParser {
	using json = nlohmann::json;
	
	enum JsonTypes {
		DEFAULT,
		OBJECT,
		ARRAY,
		STRING,
		LONG,
		DOUBLE,
		BOOL
	} JSONTYPES;

public:

	enum TYPE {
		NOTYPE,
		OBJECT,
		ARRAY,
		STRING,
		LONG,
		DOUBLE,
		BOOL
	};

public:
	JsonParser(const std::string &path);
	~JsonParser();
	dems::config::Config makeConfigFromJson();
	void makeJsonFromConfig(dems::config::Config &conf);
	dems::config::Config getConfig() const {
		return _conf;
	};

private:
	void recursiveObj(json &temp, dems::config::Config &conf);
	void chooseTypeFromJson(json::value_t type, json::value_type &value, dems::config::ConfigValue &newValue);
	void recursiveArray(json &temp, dems::config::ConfigArray &array);

private:
	std::string _path;
	std::ifstream _stream;
	dems::config::Config _conf;
};

} // Zia