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

    chooseTypeFromJson(val.type(), val, arrayValue);
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
    std::cout << iter.key() << ":" << iter.value() << std::endl; // DEBUG
    conf.insert({std::string(key), newValue});
  }
}

dems::config::Config JsonParser::makeConfigFromJson()
{
  json complete = json::parse(_stream);
  std::cout << "--- DEBUG ---" << std::endl << std::endl;
  recursiveObj(complete, _conf);
  std::cout << "\n---  FIN  ---" << std::endl << std::endl;
  return (_conf);
}

  void JsonParser::makeJsonFromConfig(dems::config::Config &conf)
  {
    for(auto &it : conf)
    {
      printf("Type of %s %i\n", it.first.c_str(), conf[it.first].v.index());
      if (conf[it.first].v.index() == JSONTYPES::BOOL)
        printf("%s IS A GROS BOOL", it.first.c_str());
    }
  }

} // Zia

// int main(int ac, char **av)
// {
//   std::string temp(av[1]);
//   std::string path("oui.json");
//   Zia::JsonParser2 test(temp);

//   test.printJson();
  
//   return 0;
// }
