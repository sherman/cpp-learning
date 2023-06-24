//
// Created by sherman on 16.08.19.
//

#include <string>
#include <iostream>
#include <unordered_map>
#include "Arguments.h"
#include <benchmark/benchmark.h>
#include "HashMap.h"

using namespace std;

static int MAX_ELTS = 1000000;

static void copy(benchmark::State &state) {
    std::string text = "text";
    std::vector<int> data(MAX_ELTS);
    for (int i = 0; i < MAX_ELTS; i++) {
        data.push_back(i);
    }
    Arguments args(1, text);

    for (auto _: state) {
        vector<int> res = Arguments::modifyCopy(data);
    }
}

static void modify(benchmark::State &state) {
    auto text = "text";
    std::vector<int> data(MAX_ELTS);
    for (int i = 0; i < MAX_ELTS; i++) {
        data.push_back(i);
    }
    Arguments args(1, text);

    for (auto _: state) {
        vector<int> res = Arguments::modify(data);
    }
}

static void setElements(benchmark::State &state) {
    auto elements = state.range(0);
    cout << "Num of elements:" << elements << endl;

    HashMap map(static_cast<int>(elements));

    for (auto _: state) {
        for (int i = 0; i < elements; i++) {
            map.set({i, "test"});
        }
    }
}

static void setElementsBaseline(benchmark::State &state) {
    size_t elements = state.range(0);
    cout << "Num of elements:" << elements << endl;

    unordered_map<int, string> map(elements);

    for (auto _: state) {
        for (int i = 0; i < elements; i++) {
            map[i] = "test";
        }
    }
}

//BENCHMARK(copy)->Iterations(1000);
//BENCHMARK(modify)->Iterations(1000);

BENCHMARK(setElements)->Arg(256)->Iterations(100000);
BENCHMARK(setElementsBaseline)->Arg(256)->Iterations(100000);

BENCHMARK_MAIN();
