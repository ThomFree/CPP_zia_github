/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** logger
*/

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <experimental/filesystem>
#include "HandlerFilePath.hpp"
#include "dems-api/Stage.hpp"
#include "dems-api/Config.hpp"

static constexpr char MODULE_NAME[] = "GuiLogger";

extern "C" {

std::string registerHooks(dems::StageManager &manager) {
	std::cout << "Module GUILogger is working..." << std::endl;
	manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = std::get<std::string>(gui["logPath"].v);
		std::ofstream ofs(logPath, std::ofstream::app);		

		ofs << "--- Establishing Request ---" << std::endl 
				<< "\t" << "Stage: Request FIRST" << std::endl;
		std::cout << "Stage: Request FIRST" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = std::get<std::string>(gui["logPath"].v);
		std::ofstream ofs(logPath, std::ofstream::app);

		ofs << "\t" << "Stage: Request MIDDLE" << std::endl;
		std::cout << "Stage: Request MIDDLE" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = std::get<std::string>(gui["logPath"].v);
		std::ofstream ofs(logPath, std::ofstream::app);

		ofs << "\t" << "Stage: Request END" << std::endl
				<< "--- Request done ---" << std::endl << std::endl;
		std::cout << "Stage: Request END" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = "./etc/zia/log/";

  	if (!(gui.find("logPath") == gui.end())) {
			logPath = std::get<std::string>(gui["logPath"].v);
		} else {
			dems::config::ConfigValue temp;

			temp.v = logPath;
			std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["GuiLogger"].v)["logPath"] = temp;
		}

		GUILogger::HandlerFilePath handler(logPath);
		logPath = handler.handleFilePath(ctx.config);
		std::get<dems::config::ConfigObject>(std::get<dems::config::ConfigObject>(ctx.config["modules"].v)["GuiLogger"].v)["logPath"].v = logPath;

		std::ofstream ofs(logPath, std::ofstream::out);

		ofs << "--- Establishing connection ---" << std::endl 
				<< "\t" << "Stage: Connection FIRST" << std::endl;
		std::cout << "[GUILoggerModule] Writing in file " << logPath << std::endl;
		std::cout << "Stage: Connection FIRST" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = std::get<std::string>(gui["logPath"].v);
		std::ofstream ofs(logPath, std::ofstream::app);
		
		ofs << "\t" << "Stage: Connection MIDDLE" << std::endl;
		std::cout << "Stage: Connection MIDDLE" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	manager.connection().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = std::get<std::string>(gui["logPath"].v);
		std::ofstream ofs(logPath, std::ofstream::app);

		ofs << "\t" << "Stage: Connection END" << std::endl;
		ofs << "--- Connection Done ---" << std::endl << std::endl;
		std::cout << "Stage: Connection END" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = std::get<std::string>(gui["logPath"].v);
		std::ofstream ofs(logPath, std::ofstream::app);

		ofs << "--- Establishing disconnection ---" << std::endl 
				<< "\t" << "Stage: Disonnection FIRST" << std::endl;
		std::cout << "Stage: Disconnection FIRST" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = std::get<std::string>(gui["logPath"].v);
		std::ofstream ofs(logPath, std::ofstream::app);

		ofs << "\t" << "Stage: Disconnection MIDDLE" << std::endl;
		std::cout << "Stage: Disconnection MIDDLE" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	manager.disconnect().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
		auto modules = std::get<dems::config::ConfigObject>(ctx.config["modules"].v);
  	auto gui = std::get<dems::config::ConfigObject>(modules["GuiLogger"].v);
		std::string logPath = std::get<std::string>(gui["logPath"].v);
		std::ofstream ofs(logPath, std::ofstream::app);

		ofs << "\t" << "Stage: Disconnection END" << std::endl;
		ofs << "--- Disconnection Done ---" << std::endl;
		std::cout << "Stage: Disconnection END" << std::endl;
		ofs.close();
		return dems::CodeStatus::OK;
	});

	return MODULE_NAME;
}

};