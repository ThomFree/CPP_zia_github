//
// EPITECH PROJECT, 2018
// Zia
// File description:
// JsonParser.cpp
//

#include "JsonParser.hpp"
#include <iomanip>
#include <cstdlib>
#include <variant>
#include <algorithm>

namespace Zia {

using json = nlohmann::json;

JsonParser::JsonParser(const std::string &path) : _path(path)
{
	_stream.open(_path, std::ifstream::in);
}

JsonParser::~JsonParser()
{
	_stream.close();
}

void JsonParser::chooseTypeFromJson(json::value_t type, json::value_type &value, dems::config::ConfigValue &newValue)
{
	switch (type) {
	case (json::value_t::string):
		newValue.v = value.get<std::string>();
		break;
	case (json::value_t::number_integer):
		newValue.v = value.get<long long>();
		break;
	case (json::value_t::number_unsigned):
		newValue.v = value.get<long long>();
		break;
	case (json::value_t::boolean):
		newValue.v = value.get<bool>();
		break;
	case (json::value_t::array):
		break;
	default:
		std::cerr << "Unknown type on Json. Might be a float." << std::endl;
		break;
	}
}

void JsonParser::recursiveArray(json &temp, dems::config::ConfigArray &array) {
  json::value_type val = temp;

  for (unsigned int i = 0; i < val.size(); i++) {
    dems::config::ConfigValue arrayValue;

    chooseTypeFromJson(val[i].type(), val[i], arrayValue);
    if (val[i].type() == json::value_t::array) {
      dems::config::ConfigArray newArray;
      dems::config::ConfigValue newValue;

      recursiveArray(val.at(i), newArray);
      newValue.v = newArray;
      array.push_back(newValue);
    }
    array.push_back(arrayValue);
  }
}

void JsonParser::recursiveObj(json &temp, dems::config::Config &conf)
{
	for (json::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
		json::value_type val = iter.value();
		auto key = iter.key();
		dems::config::ConfigValue newValue;
		dems::config::ConfigObject newObj;

		if (val.type() == json::value_t::object) {
			recursiveObj(*iter, newObj);
			newValue.v = newObj;
		} else if (val.type() != json::value_t::array) {
			chooseTypeFromJson(val.type(), val, newValue);
		} else {
			dems::config::ConfigArray array;
			recursiveArray(*iter, array);
			newValue.v = array;
		}
		conf.insert({std::string(key), newValue});
	}
}

dems::config::Config JsonParser::makeConfigFromJson()
{
	json complete = json::parse(_stream);
	recursiveObj(complete, _conf);
	return (_conf);
}

void JsonParser::writeFromConfig(std::pair<const std::string, dems::config::ConfigValue> &obj, TYPE type, json &file, bool isArray)
{
  switch (type) {
  case (TYPE::BOOL):
    file[obj.first] = std::get<bool>(obj.second.v);
    break;
  case (TYPE::STRING):
    file[obj.first] = std::get<std::string>(obj.second.v);
    break;
  case (TYPE::LONG):
    if (isArray) {
      file.push_back(std::get<long long>(obj.second.v));
    }
    else
      file[obj.first] = std::get<long long>(obj.second.v);
    break;
  case (TYPE::ARRAY):
    file[obj.first] = {};
    break;
  case (TYPE::OBJECT):
    file[obj.first] = {};
    break;
  default:
    break;
  }
}

void JsonParser::traverseArray(dems::config::ConfigArray &array, json &jsonFile)
{
  for (unsigned int i = 0; i < array.size(); i++) {
    if (array[i].v.index() == TYPE::ARRAY) {
      jsonFile += {{}};
      traverseArray(std::get<dems::config::ConfigArray>(array[i].v), jsonFile);
    }
    switch(array[i].v.index()) {
    case (TYPE::LONG):
      jsonFile += std::get<long long>(array[i].v);
      break;
    case (TYPE::STRING):
      jsonFile += std::get<std::string>(array[i].v);
      break;
    case (TYPE::BOOL):
      jsonFile += std::get<bool>(array[i].v);
      break;
    default:
      break;
    }
  }
}

void JsonParser::traverseObj(dems::config::ConfigObject &conf, json &jsonFile, bool isArray)
{
  TYPE type = NOTYPE;
  for (auto &it : conf) {
    type = static_cast<TYPE>(conf[it.first].v.index());
    writeFromConfig(it, type, jsonFile, isArray);
    if (type == TYPE::OBJECT)
      traverseObj(std::get<dems::config::ConfigObject>(it.second.v), jsonFile[it.first], false);
    else if (type == TYPE::ARRAY) {
      traverseArray(std::get<dems::config::ConfigArray>(it.second.v), jsonFile[it.first]);
    }
  }
}

void JsonParser::makeJsonFromConfig(dems::config::Config &conf, const std::string &nameFile)
{
  std::ofstream file(nameFile);
  json jsonFile;
  traverseObj(conf, jsonFile, false);
  file << std::setw(4) << jsonFile << std::endl;
  file.close();
}

} // Zia

