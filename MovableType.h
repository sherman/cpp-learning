//
// Created by sherman on 16.08.19.
//

#ifndef CPPLEARNING_MOVABLETYPE_H
#define CPPLEARNING_MOVABLETYPE_H

#include <string>
#include <vector>

class MovableType {
public:
    explicit MovableType(int size) {
        data = std::vector<int>(size);

        for (int i = 0; i < size; i++) {
            data.push_back(i);
        }
    }

    MovableType(MovableType && dataContainer) noexcept {
        data = std::move(dataContainer.data);
    }

    std::vector<int> & getData();

private:
    std::vector<int> data;
};


#endif //CPPLEARNING_MOVABLETYPE_H
