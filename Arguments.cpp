//
// Created by sherman on 05.08.2019.
//

#include "Arguments.h"
#include <iostream>

bool Arguments::hasText(std::string& search) {
    std::size_t found = text_.find(search);
    std::cout << found << std::endl;
    return found != std::string::npos;
}