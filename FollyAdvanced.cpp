
#include <folly/futures/Future.h>
#include <folly/executors/ThreadedExecutor.h>
//#include <iostream>

using namespace folly;
using namespace folly::futures;
using namespace std;

static void print(int value) {
    //std::cout  << value << std::endl;
}

static void futures() {
    Promise<int> p;
    p.getFuture().thenValue(print);

}

int main() {
    ::futures();

    return 0;
}