/*
** EPITECH PROJECT, 2019
** tests
** File description:
** main
*/

#include <iostream>
#include "header.hpp"

template<typename T>
T A::get()
{
	std::cout << "Generic" << std::endl;
	return (T)0;
}

template<>
int A::get()
{
	std::cout << "Int" << std::endl;
	return 0;
}

template<>
char *A::get()
{
	std::cout << "char *" << std::endl;
	return nullptr;
}

template<>
A A::get()
{
	std::cout << "class A" << std::endl;
	return A();
}

int main(int ac, char *av[])
{
	A::get<char>();
	A::get<int>();
	A::get<char*>();
	A::get<A>();

	return 0;
}