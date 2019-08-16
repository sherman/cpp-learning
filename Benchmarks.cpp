//
// Created by sherman on 16.08.19.
//

#include <string>
#include <iostream>
#include "Arguments.h"
#include <benchmark/benchmark.h>

using namespace std;

static int MAX_ELTS = 1000000;

static void copy(benchmark::State & state) {
    std::string text = "text";
    std::vector<int> data(MAX_ELTS);
    for (int i = 0; i < MAX_ELTS; i++) {
         data.push_back(i);
    }
    Arguments args(1, text);

    for (auto _ : state) {
        vector<int> res = args.modifyCopy(data);
    }
}

static void modify(benchmark::State & state) {
    std::string text = "text";
    std::vector<int> data(MAX_ELTS);
    for (int i = 0; i < MAX_ELTS; i++) {
        data.push_back(i);
    }
    Arguments args(1, text);

    for (auto _ : state) {
        vector<int> res = args.modify(data);
    }
}

BENCHMARK(copy)->Iterations(1000);
BENCHMARK(modify)->Iterations(1000);

BENCHMARK_MAIN();
