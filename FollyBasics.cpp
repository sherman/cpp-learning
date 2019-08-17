//
// Created by sherman on 17.08.19.
//
#include <string>
#include <iostream>
#include <folly/container/Foreach.h>
#include <vector>
#include "Arguments.h"
#include <folly/Bits.h>

using namespace std;
using namespace folly;

static int MAX_ELTS = 1000000;

static void iterate() {
    std::string text = "text";
    std::vector<int> data(MAX_ELTS);
    for (int i = 0; i < MAX_ELTS; i++) {
        data.push_back(i);
    }
    Arguments args(1, text);

    FOR_EACH_RANGE(i, 1, 100) {
        vector<int> res = args.modifyCopy(data);
    }
}

static void bits() {
    const int value1 = 0x11100;
    assert(popcount(value1) == 3);

    const int value2 = 0x00111001;
    assert(popcount(value2) == 4);

    const int value3 = 10; // 1010
    const int expected = 1342177280; // 1010000000000000000000000000000
    assert(bitReverse(value3) == expected);
}

int main() {
    iterate();
    bits();

    return 0;
}
