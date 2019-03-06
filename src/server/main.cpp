/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** main
*/

#include "utils/ParseArgs.hpp"
#include "utils/JsonParser.hpp"
#include "utils/ConfigWatcher.hpp"
#include "WebsiteManager.hpp"

int main(int ac, const char * const av[])
{
	try {
		Zia::ParseArgs parser(ac, av);
		if (parser.hasError()) {
			std::cerr << parser.getError() << std::endl;
			return 84;
		}
		if (parser.actionHasBeenDone())
			return 0;


		std::string temp(av[1]);
		std::string path("oui.json");
		Zia::JsonParser test(temp);

		dems::config::Config oui = test.makeConfigFromJson();

		std::cout << "[Zia] Starting..." << std::endl;
		Zia::WebsiteManager master(parser);

		master.launch();

		// test.makeJsonFromConfig(oui, path);
		//	master.launch();
	} catch (const std::exception &err) {
		std::cerr << err.what() << std::endl;
		return 84;
	}
	return 0;
}