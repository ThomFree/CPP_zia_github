/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** HttpHeader
*/

#include <iostream>

#include "HttpHeader.hpp"

namespace Zia {
std::string &HttpHeader::operator[](const std::string &headerName)
{
	return _headers[headerName];
}

const std::string &HttpHeader::getHeader(const std::string &headerName) const
{
	return _headers.at(headerName);
}

std::string HttpHeader::getWholeHeaders() const
{
	std::string buffer;

	for (auto it : _headers)
		buffer.append(it.second + "\r\n");
	return buffer;
}

void HttpHeader::setHeader(const std::string &headerName, const std::string &value)
{
	_headers.emplace(headerName, value);
}
}