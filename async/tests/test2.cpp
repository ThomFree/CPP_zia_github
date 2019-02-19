/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** test2
*/

#include <utility>
#include <future>
#include <iostream>
#include <type_traits>

struct Wrap {
    template<typename F>

    Wrap(F &&fn)
	{
            std::cout << this->type(std::move(fn)) << std::endl;
	}

    template<typename F>
    auto type(F &&fn) -> decltype(fn())
        {
            return 12;
        }
};

int main()
{
    Wrap w(std::move([]() -> int { std::cout << "Hello world!" << std::endl; return 5; }));

    return 0;
}
