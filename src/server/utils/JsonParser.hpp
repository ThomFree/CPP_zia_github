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
public:
	using json = nlohmann::json;

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
	void makeJsonFromConfig(dems::config::Config &conf, const std::string &fileName);
	
	dems::config::Config getConfig() const {
		return _conf;
	};

private:
	void recursiveObj(json &temp, dems::config::Config &conf);
	void chooseTypeFromJson(json::value_t type, json::value_type &value, dems::config::ConfigValue &newValue);
	void recursiveArray(json &temp, dems::config::ConfigArray &array);
	void writeFromConfig(std::pair<const std::string, dems::config::ConfigValue> &obj, TYPE type, json &file, bool isArray);
	void traverseObj(dems::config::ConfigObject &conf, json &jsonFile, bool isArray);
	void traverseArray(dems::config::ConfigArray &array, json &jsonFile);

private:
	std::string _path;
	std::ifstream _stream;
	dems::config::Config _conf;
};

} // Zia