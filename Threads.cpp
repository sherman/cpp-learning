#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std::chrono_literals;

namespace threads {

    static void initializer(std::promise<int> *promise) {
        std::cout << "Inside thread" << std::endl;
        promise->set_value(42);
    }

    static void blocking(std::promise<int> *promise) {
        std::cout << "Blocking thread started" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "Blocking thread finished" << std::endl;
        promise->set_value(42);
    }
}