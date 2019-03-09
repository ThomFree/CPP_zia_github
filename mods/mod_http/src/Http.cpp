/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Http
*/

#include "Http.hpp"

namespace mod {

Http::Http(dems::Context &ctx) : _ctx(ctx)
{}

void Http::parse()
{
	// Parse context raw int context headers...
}

void Http::interpret()
{
	// Interpret context headers and do the request
	// Make the response
	_ctx.response.body = "HELLO WORLD.";
}

}