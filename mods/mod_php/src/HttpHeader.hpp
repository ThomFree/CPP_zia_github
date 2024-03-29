/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** HttpHeader
*/

#include <unordered_map>

#include "dems-api/Heading.hpp"

#pragma once

namespace Zia {
class HttpHeader : public dems::header::IHeaders {
	public:
		HttpHeader() = default;
		~HttpHeader() = default;

		std::string &operator[](const std::string &headerName) override;
		const std::string &getHeader(const std::string &headerName) const override;
		std::string getWholeHeaders() const override;
		void setHeader(const std::string &headerName, const std::string &value) override;
		const std::unordered_map<std::string, std::string> &getMap() const { return _headers; }

	private:
		std::unordered_map<std::string, std::string> _headers;
		std::string badApi = "";
};
}