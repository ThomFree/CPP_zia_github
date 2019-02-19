/*
** EPITECH PROJECT, LIFE_DURATION19
** async
** File description:
** Main de test
*/

#include <unistd.h>
#include <iostream>
#include "async/ThreadPool.hpp"


#include <future>
#include <thread>

const int LIFE_DURATION = 1;

class A {
	public:
		static int f() {
			int a = 0;
			while (a != LIFE_DURATION) {
				sleep(1);
			a++;
		}
		return 1;
	}
		int a() {
			int a = 0;
			while (a != LIFE_DURATION) {
				sleep(1);
				a++;
			}
			return 2;
		}
};

static int f()
{
	int a = 0;
	while (a != LIFE_DURATION) {
		sleep(1);
		a++;
	}
	return 3;
}

int main()
{
	async::ThreadPool tp(1);

	sleep(2);

	// post lambda 1
	tp.post(std::function<int()>([](){
		int a = 0;
		while (a != LIFE_DURATION) {
			sleep(1);
			a++;
		}
		return 4;
	}));

//	sleep(0.5);

	// post lambda 2
	tp.post(std::function<int()>([](){
	int a = 0;
	while (a != LIFE_DURATION) {
			sleep(1);
			a++;
		}
		return 5;
	}));

//	sleep(0.5);

	// post simple function
	tp.post(std::function<int()>(f));

//	sleep(0.5);

	// post static method
	tp.post(std::function<int()>(&A::f));

//	sleep(0.5);

	// post method with binded with reference
	A a;
	std::function<int()> task(std::bind(&A::a, std::ref(a)));
	tp.post(task);

	sleep(10 + 2);

	return 0;
}