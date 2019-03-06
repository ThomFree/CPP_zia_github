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

  void JsonParser::writeFromConfig(std::pair<const std::string, dems::config::ConfigValue> &obj, TYPE type, json &file, std::string &objName)
  {
    if (objName.empty()) {
      std::cout << "nom object nul" << std::endl;
      switch (type)
      {
      case (TYPE::BOOL):
        file[obj.first] = std::get<bool>(obj.second.v);
        break;
      case (TYPE::STRING):
        file[obj.first] = std::get<std::string>(obj.second.v);
        break;
      case (TYPE::LONG):
        file[obj.first] = std::get<long long>(obj.second.v);
        break;
      case (TYPE::ARRAY):
        file[obj.first] = {{}};
        objName = obj.first;
        break;
      case (TYPE::OBJECT):
        file[obj.first] = {};
        objName = obj.first;
        break;
      default:
        break;
      }
    } else {
      std::cout << "Je vais écrire dans " << objName << " : " << obj.first << std::endl;
      switch (type) {
      case (TYPE::BOOL):
        file[objName][obj.first] = std::get<bool>(obj.second.v);
        break;
      case (TYPE::STRING):
        file[objName][obj.first] = std::get<std::string>(obj.second.v);
        break;
      case (TYPE::LONG):
        file[objName][obj.first] = std::get<long long>(obj.second.v);
        break;
      case (TYPE::ARRAY):
        file[objName][obj.first] = {{}};
        objName = obj.first;
        break;
      case (TYPE::OBJECT):
        file[objName][obj.first] = {};
        std::cout << "Oui = " << file << std::endl;
        objName = obj.first;
        break;
      default:
        break;
      }
    }
  }

  void JsonParser::traverseObj(dems::config::ConfigObject &conf, json &jsonFile, std::string &objName)
  {
    TYPE type = NOTYPE;
    std::cout << "Entrée dans " << objName << std::endl;

    for (auto &it : conf) {
      type = static_cast<TYPE>(conf[it.first].v.index());
      writeFromConfig(it, type, jsonFile, objName);

      //std::cout << "NOM DE LA VALUE = " << it.first << std::endl;
      if (!(objName.empty()) && type == TYPE::OBJECT) {
        //std::cout << "NOM DE L'OBJET = " << objName << std::endl;
        json tempJson;
        std::string tempObj = objName;

        traverseObj(std::get<dems::config::ConfigObject>(it.second.v), jsonFile, objName);
        // std::cout << "Obj principal : " << objName << " - objet secondaire : " << tempObj << std::endl << std::endl << std::setw(4) << tempJson << std::endl << std::endl;
        // jsonFile[objName][tempObj] = tempJson[tempObj];
        // objName = it.first;
        //std::cout << "Dépile" << std::endl;
      }
      //std::cout << "Sortie : " << std::endl << jsonFile << std::endl;
    }
    std::cout << "J'ai fini l'object " << objName << std::endl;
    objName = "";
  }

  void JsonParser::makeJsonFromConfig(dems::config::Config &conf, const std::string &nameFile)
  {
    std::ofstream file(nameFile);
    json jsonFile;
    std::string temp("");

    traverseObj(conf, jsonFile, temp);
    file << std::setw(4) << jsonFile << std::endl;
    file.close();
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
