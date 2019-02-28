/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** HttpHeader
*/

#pragma once

#include "api/Heading.hpp"

namespace Zia::api {
class HttpHeader : public dems::header::IHeaders {
public:
	HttpHeader() = default;
	~HttpHeader() = default;

	std::string &operator[](const std::string &headerName) override;
	std::string &getHeader(const std::string &headerName) const override;
	std::string getWholeHeaders() const override;
	void setHeader(const std::string &headerName, const std::string &value) override;
};
}