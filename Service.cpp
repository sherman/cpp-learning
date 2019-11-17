//
// Created by sherman on 11.11.19.
//

#include "Service.h"
#include <iostream>

void HeartbeatImpl::heartbeat(std::string & message) {
    std::cout << message << std::endl;
}

