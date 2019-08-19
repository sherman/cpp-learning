//
// Created by sherman on 18.08.19.
//

namespace util {
    static unsigned int nextPowerOfTwo(unsigned int value) {
        --value;
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        ++value;
        return value;
    }
}