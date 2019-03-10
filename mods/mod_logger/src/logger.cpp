/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** logger
*/

#include <string>
#include <iostream>
#include "dems-api/Stage.hpp"

static constexpr char MODULE_NAME[] = "Logger";

extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
	std::cout << "ON REGIsTER PAS DES HOOKS NOUS ?" << std::endl;
	manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Request FIRST" << std::endl;
		return dems::CodeStatus::OK;
	});

	manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Request MIDDLE" << std::endl;
		return dems::CodeStatus::OK;
	});

	manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Request END" << std::endl;
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToFirst(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Connection FIRST" << std::endl;
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToMiddle(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Connection MIDDLE" << std::endl;
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToEnd(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Connection END" << std::endl;
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToFirst(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Disconnection FIRST" << std::endl;
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToMiddle(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Disconnection MIDDLE" << std::endl;
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToEnd(0, MODULE_NAME, [](dems::Context &) {
		std::cout << "Stage: Disconnection END" << std::endl;
		return dems::CodeStatus::OK;
	});

	return MODULE_NAME;
}

};