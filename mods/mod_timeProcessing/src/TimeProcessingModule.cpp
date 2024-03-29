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
		long long int timeMS = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});

	manager.request().hookToMiddle(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int timeMS = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});

	manager.request().hookToEnd(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int timeMS = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});

	/*
	** Connection
	*/

	manager.connection().hookToFirst(99, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto timer = std::get<dems::config::ConfigObject>(modules["TimeProcessing"].v);
		long long int timeMS = 50;

  	if (!(timer.find("timeMS") == timer.end())) {
			timeMS = std::get<long long>(timer["timeMS"].v);
		} else {
			dems::config::ConfigValue temp;

			temp.v = timeMS;
			std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"] = temp;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToMiddle(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int timeMS = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToEnd(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int timeMS = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});
	
	/*
	** Disconnection
	*/

	manager.disconnect().hookToFirst(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int timeMS = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToMiddle(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int timeMS = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToEnd(99, MODULE_NAME, [](dems::Context &ctx) {
		long long int timeMS = std::get<long long>(std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["TimeProcessing"].v)["timeMS"].v);

		std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
		return dems::CodeStatus::OK;
	});

	return MODULE_NAME;
}

};