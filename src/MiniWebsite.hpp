/*
** EPITECH PROJECT, 2019
** $
** File description:
** MiniWebsite
*/

#include <vector>
#include "MiniMediator.hpp"

#pragma once

namespace Pizzia {

class MiniWebsite {
	public:
		MiniWebsite();
		~MiniWebsite();

	private:
        void acceptClient(); // TODO faire le accept TCP
        void addClient(); // Ajoute un client dans le vector
    
    private:
        std::vector<MiniMediator> _clients;
};

}