/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** test3
*/

#pragma once
#include <utility>
#include <type_traits>
#include <memory>
#include <functional>

class Task {
public:

template<typename T, typename... Args>
	explicit Task(const T &data, Args&&... args) :
	_ptr(new T(data), [](void *ptr) {
			delete static_cast<T*>(ptr);
		}),
	invoke([args...](void *ptr) {
			return (*static_cast<T*>(ptr))(args...);
		})
	{
		std::cout << "copy" << std::endl;
	}

	template<typename T, typename dT = std::decay_t<T>, typename... Args>
	explicit Task(T &&data, Args&&... args) :
	_ptr(new dT(std::forward<T>(data)), [](void *ptr) {
			delete static_cast<dT*>(ptr);
		}),
	invoke([args...](void *ptr) {
			return (*static_cast<dT*>(ptr))(args...);
		})
	{
		std::cout << "move" << std::endl;
	}

	auto operator()() const -> int
	{
		auto res = invoke(_ptr.get());
		return res;
	}

private:
	std::unique_ptr<void, void (*)(void*)> _ptr;
	int (*invoke)(void*) = nullptr;
};

