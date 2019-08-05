//
// Created by sherman on 05.08.2019.
//

#include "Arguments.h"
#include <iostream>

bool Arguments::hasText(const std::string& search) {
    std::size_t found = text_.find(search);
    std::cout << found << std::endl;
    return found != std::string::npos;
}

std::vector<int> Arguments::modifyCopy(std::vector<int> data) {
    for (auto& elt : data) {
        elt = -1;
    }

    return data;
}

std::vector<int> Arguments::modify(std::vector<int> &data) {
    for (auto& elt : data) {
        elt = -1;
    }

    return data;
}

std::vector<int> & Arguments::returnByRef(std::vector<int> &data) {
    for (auto& elt : data) {
        elt = -1;
    }

    return data;
}