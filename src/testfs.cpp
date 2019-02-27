/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** test
*/

#include <iostream>
#include <filesystem>
#include <fstream>

int main()
{
	//std::filesystem::create_directories("sandbox/a/b");
	//std::ofstream("sandbox/file1.txt");
	//std::ofstream("sandbox/file2.txt");
	 for(auto& p: std::filesystem::directory_iterator("sandbox"))
		 std::cout << p.path() << '\n';
	// std::filesystem::remove_all("sandbox");
}