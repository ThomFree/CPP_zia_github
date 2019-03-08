/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** timer for processing
*/

#include <string>
#include <iostream>
#include <thread>
#include "dems-api/Stage.hpp"

static constexpr char MODULE_NAME[] = "TimeProcessing";

// Add "timeMS" in Module config in order to slow down the process

extern "C" {

std::string registerHooks(dems::StageManager &manager) {

	std::cout << "Module TimeProcessing is working..." << std::endl;

	/*
	** Request
	*/

	manager.request().hookToFirst(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		return dems::CodeStatus::OK;
	});

	manager.request().hookToMiddle(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		return dems::CodeStatus::OK;
	});

	manager.request().hookToEnd(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		return dems::CodeStatus::OK;
	});

	/*
	** Connection
	*/

	manager.connection().hookToFirst(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);
		std::this_thread::sleep_for(std::chrono::milliseconds(time));

		(std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v)) = 50;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		return dems::CodeStatus::OK;
	});

	manager.connection().hookToMiddle(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToEnd(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		return dems::CodeStatus::OK;
	});
	
	/*
	** Disconnection
	*/

	manager.disconnect().hookToFirst(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToMiddle(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToEnd(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int time = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		return dems::CodeStatus::OK;
	});

	return MODULE_NAME;
}

};