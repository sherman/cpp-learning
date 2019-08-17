//
// Created by sherman on 17.08.19.
//
#include <string>
#include <iostream>
#include <folly/container/Foreach.h>
#include <vector>
#include "Arguments.h"

using namespace std;
using namespace folly;

static int MAX_ELTS = 1000000;


int main() {
    std::string text = "text";
    std::vector<int> data(MAX_ELTS);
    for (int i = 0; i < MAX_ELTS; i++) {
        data.push_back(i);
    }
    Arguments args(1, text);

    FOR_EACH_RANGE(i, 1, 100) {
        vector<int> res = args.modifyCopy(data);
    }

    return 0;
}
