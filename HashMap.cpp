//
// Created by sherman on 18.08.19.
//

#include <iterator>
#include "HashMap.h"
#include "Utils.cpp"

HashMap::HashMap(const int size) {
    capacity_ = max(util::nextPowerOfTwo(size), MIN_SIZE);
    data_ = new Object[capacity_];
    size_ = 0;

    for (int i = 0; i < capacity_; i++) {
        data_[i] = EMPTY;
    }
}

HashMap::~HashMap() {
    delete [] data_;

    capacity_ = 0;
    size_ = 0;
}

void HashMap::set(const Object & value) {
    if (capacity_ == getSize()) {
        resize();
    }

    int index = hash(value.id);

    //cout << index << endl;

    int target = -1;
    for (int i = index; i >= 0; i--) {
        //cout << i << endl;
        auto curr = &data_[i];

        // found empty slot
        if (curr->isEmpty()) {
            //cout << "Empty slot 1" << endl;
            target = i;
            break;
        }

        // a data is occupied by the same id
        if (curr->id == value.id) {
            //cout << "Occupied slot 1" << endl;
            target = i;
            break;
        }
    }

    //cout << "Index:" << target << endl;

    if (target == -1 && index + 1 < capacity_) {
        for (int i = index + 1; i < capacity_; i++) {
            //cout << i << endl;
            auto curr = &data_[i];

            // found empty slot
            if (curr->isEmpty()) {
                //cout << "Empty slot 2" << endl;
                target = i;
                break;
            }

            // a data is occupied by the same id
            if (curr->id == value.id) {
                //cout << "Occupied slot 2" << endl;
                target = i;
                break;
            }
        }
    }

    if (target == -1) {
        throw "No slot available!";
    }

    //new(data_ + sizeof(Object) * target) Object(value);
    data_[target] = value;
    size_++;
}

int HashMap::getSize() const {
    return size_;
}

int HashMap::getCapacity() const {
    return capacity_;
}

void HashMap::resize() {

}

unsigned int HashMap::hash(const unsigned int value) const {
    return ((value ^ (value >> 16)) * MAGIC) >> 24;
}

const Object & HashMap::get(const int id) const {
    //cout <<"Getting " << id << endl;

    int index = hash(id);

    for (int i = index; i >= 0; i--) {
        auto curr = &data_[i];

        if (!curr->isEmpty() && curr->id == id) {
            return *curr;
        }
    }

    if (index + 1 < capacity_) {
        for (int i = index + 1; i < capacity_; i++) {
            auto curr = &data_[i];

            if (!curr->isEmpty() && curr->id == id) {
                return *curr;
            }
        }
    }

    // not found
    return EMPTY;
}

HashMap::HashMap(const HashMap & copy) {
    capacity_ = copy.capacity_;
    size_ = copy.size_;
    data_ = new Object[capacity_];

    for (int i = 0; i < copy.getSize(); i++) {
        set(copy.data_[i]);
    }
}

HashMap & HashMap::operator=(const HashMap & copy) {
    throw "Implement me!";
}
