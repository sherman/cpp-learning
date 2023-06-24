//
// Created by sherman on 05.08.2019.
//

#pragma once


#include <string>
#include <iostream>
#include <vector>
#include <jmorecfg.h>

class Arguments {
public:
    Arguments(int value, const std::string & text) {
        value_ = value;
        text_ = text;
    }

    bool hasText(const std::string & search);

    static std::vector<int> modifyCopy(std::vector<int> data);

    static std::vector<int> modify(std::vector<int> & data);

    static std::vector<int> & returnByRef(std::vector<int> & data);

private:
    int value_;
    std::string text_;
};

