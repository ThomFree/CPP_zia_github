/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** main
*/

#include "utils/ParseArgs.hpp"
#include "utils/JsonParser.hpp"
#include "WebsiteManager.hpp"

namespace Zia {
std::atomic<bool> RESTART_ZIA(true);
}

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

		while (Zia::RESTART_ZIA) {
			Zia::RESTART_ZIA = false;

			std::cout << "[Zia] Starting..." << std::endl;
			Zia::WebsiteManager master(parser);

			master.launch();
		}

	} catch (const std::exception &err) {
		std::cout << err.what() << std::endl;
		return 84;
	}
	return 0;
}