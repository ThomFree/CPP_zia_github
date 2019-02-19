/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** test
*/

#include <future>
#include <thread>
#include <type_traits>
#include <memory>
#include <utility>
#include <iostream>
#include <queue>

#include "../SafeQueue.hpp"

/*
template<class F>
struct get_signature;

template<class R>
struct get_signature<R(*)()>{
  typedef R type;
};
*/
/*
template<class R, class A1>
struct get_signature<R(*)(A1)>{
  typedef R type(A1);
};*/
/*
class


template<typename> struct check_function;
template<typename R, typename... Args>
struct check_function<R(Args...)>: public std::function<R(Args...)> {
    template<typename T,
        class = typename std::enable_if<
            std::is_same<R, void>::value
            || std::is_convertible<
                decltype(std::declval<T>()(std::declval<Args>()...)),
                R>::value>::type>
        check_function(T &&t): std::function<R(Args...)>(std::forward<T>(t)) {

		}
};

int a(check_function<int ()> f) { return f(); }
int a(check_function<int (int)> f) { return f(0); }

int x() { return 22; }
int y(int) { return 44; }

template<typename T, typename U>
struct decay_equiv : std::is_same<typename std::decay<T>::type, U>::type
{};

template <typename T, typename Container = std::deque<T>>
struct Queue : public std::queue<T, Container> {
	Queue<T, Container>() : std::queue<T, Container>() {}

	T &&Front() {
		return this->front();
	}
};

*/
template<typename R>
struct task {
private:
    std::unique_ptr<void, void(*)(void*)> ptr;
    void (*invoke)(void*) = nullptr;
    std::future<R> promise;

public:
    template<typename F, typename dF=std::decay_t<F>, typename RT =decltype( std::declval<dF&>()() )>
    task( F&& f ) : ptr(new dF(std::forward<F>(f)),
                        [](void* ptr){ delete static_cast<dF*>(ptr); }),
                    invoke([](void*ptr) {
                               std::thread(std::move(*static_cast<dF*>(ptr))).detach();
                    })
	{
        try {
            promise = (*static_cast<dF*>(ptr.get())).get_future();
        } catch (...) {
            std::cerr << "get future" << std::endl;
            exit(1);
        }
	}

    auto operator()() -> R {
        try {
            invoke( ptr.get() );
            promise.wait();
        } catch (...) {
            std::cerr << "future" << std::endl;
            exit(1);
        }
        return promise.get();
    }

    task(const task &) = delete;
    task(task &&) = default;
    task &operator=(task &&) = default;
    task() = default;
    ~task() = default;
};


#include <iostream>
#include <type_traits>

/*
int main()
{
    task<int> t(std::packaged_task<int()>([]() -> int { return 12; }));
    std::cout << t() << std::endl;

    return 0;
}

/*
int main()
{
    std::queue<std::shared_ptr<task<int>>> q;
    std::queue<task<int>> q2;

    std::packaged_task<int()> pt([]() -> int { return 0; });

    auto ptr = std::make_shared<task<int>>(std::move(std::packaged_task<int()>([]() {
                                                                                   return 7;
                                                                               })));

    q.push(ptr);

    auto &t = q.front();
    q.pop();

    auto res = (*t)();

    std::cout << "Task result is " << res << std::endl;

    q2.push(task<int>(std::move(std::packaged_task<int()>(
                                    []() -> int {
                                        return 8;
                                    }))));

    std::cout << "Size: " << q2.size() << std::endl;

    auto &&ref = q2.front();
    q2.pop();
    res = ref();

    std::cout << "Size: " << q2.size() << std::endl;

    std::cout << "Task result is " << res << std::endl;
    return 0;
}

/*
#include <iostream>
#include <utility>

struct Default {
	Default() = default;

	int foo() const { return 1; }
};

struct NonDefault {
	NonDefault() = delete;

	auto bar() const -> double { return 0.76; }
};

int main()
{
	decltype(Default().foo()) n1 = 1;

	decltype(std::declval<NonDefault>().bar()) n2 = 0.232;

	std::cout << n1 << " - " << n2 << std::endl;
}
*/

/*
template<typename T, typename U>
auto add(T x, U y) -> decltype(x)
{
	return x + y;
}

int main()
{
	std::cout << add(12.34, 12) << std::endl;
	return 0;
}
*/


/*
#include <iostream>
#include <type_traits>

// Remove cv qualifiers, array, pointer, function type

template <typename T, typename U>
struct decay_equiv :
    std::is_same<typename std::decay<T>::type, U>::type
{};

int main()
{
    std::cout << std::boolalpha
              << decay_equiv<int, int>::value << '\n'
              << decay_equiv<int&, int>::value << '\n'
              << decay_equiv<int&&, int>::value << '\n'
              << decay_equiv<const int&, int>::value << '\n'
              << decay_equiv<int[2], int*>::value << '\n'
              << decay_equiv<int(int), int(*)(int)>::value << '\n';
}
*/
