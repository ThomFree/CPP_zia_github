/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** PHP Module
*/

#include <string>
#include <iostream>
#include "dems-api/Stage.hpp"
#include "PHP.hpp"

static constexpr char MODULE_NAME[] = "PHP Module";

extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
	manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
		mod::PHP module(ctx);

		module.parse();
		return dems::CodeStatus::OK;
	});

	manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
		mod::PHP module(ctx);

		if (!module.checkForPhp())
			module.interpret();
		return dems::CodeStatus::OK;
	});

	return MODULE_NAME;
}

};