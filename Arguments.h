//
// Created by sherman on 05.08.2019.
//

#ifndef CPPLEARNING_ARGUMENTS_H
#define CPPLEARNING_ARGUMENTS_H


#include <string>
#include <iostream>
#include <jmorecfg.h>

class Arguments {
public:
    Arguments(int value, const std::string & text) {
        value_ = value;
        text_ = text;
    }

    bool hasText(const std::string& search);

private:
    int value_;
    std::string text_;
};


#endif //CPPLEARNING_ARGUMENTS_H
