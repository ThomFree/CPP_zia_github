/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** http
*/

#include <string>
#include <iostream>

#include "dems-api/Stage.hpp"

static constexpr char MODULE_NAME[] = "Http";

extern "C" {

	std::string registerHooks(dems::StageManager &manager)
	{
		std::cout << "Register Hooks for module Http" << std::endl;

		/*
		 * Parsing request to context
		 */
		manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
			return dems::CodeStatus::OK;
		});

		/*
		 * Interpret ctx
		 */
		manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
			return dems::CodeStatus::OK;
		});

		/*
		 * Ctx to response
		 */
		manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
			return dems::CodeStatus::OK;
		});
		return MODULE_NAME;
	}
};