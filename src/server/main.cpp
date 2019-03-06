/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** main
*/

#include "utils/ParseArgs.hpp"
#include "utils/JsonParser.hpp"
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

		std::cout << "[Zia] Starting..." << std::endl;
		Zia::WebsiteManager master(parser);

		master.launch();

		//Testing Making json from config
		if (ac != 2) {
			std::cerr << "Test json requires a config file to work." << std::endl;
			return 84;
		}

		std::string temp(av[1]);
		std::string path("oui.json");
		Zia::JsonParser test(temp);

		dems::config::Config oui = test.makeConfigFromJson();
		test.makeJsonFromConfig(oui, path);

		// End Testing Json [DEBUG]

	} catch (const std::exception &err) {
		std::cerr << err.what() << std::endl;
		return 84;
	}
	return 0;
}