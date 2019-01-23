/*
** EPITECH PROJECT, LIFE_DURATION19
** async
** File description:
** Main de test
*/

#include <unistd.h>
#include <iostream>
#include "async/ThreadPool.hpp"

const int LIFE_DURATION = 5;

class A {
	public:
		static void f() {
			int a = 0;
			while (a != LIFE_DURATION) {
				sleep(1);
			a++;
		}
}
		void a() {
			int a = 0;
			while (a != LIFE_DURATION) {
				sleep(1);
				a++;
			}
		}
};

static void f()
{
	int a = 0;
	while (a != LIFE_DURATION) {
		sleep(1);
		a++;
	}
}

int main()
{
	async::ThreadPool tp(1);

	sleep(2);

	// post lambda 1
	tp.post(std::bind([](){
	int a = 0;
	while (a != LIFE_DURATION) {
		sleep(1);
		a++;
	}}));

	sleep(0.5);

	// post lambda 2
	tp.post(std::bind([](){
	int a = 0;
	while (a != LIFE_DURATION) {
		sleep(1);
		a++;
	}}));

	sleep(0.5);

	// post simple function
	tp.post(std::bind(f));

	sleep(0.5);

	// post static method
	tp.post(std::bind(&A::f));

	sleep(0.5);

	// post method with binded with reference
	A a;
	tp.post(std::bind(&A::a, std::ref(a)));

	sleep(LIFE_DURATION + 2);

	return 0;
}