#include <utility>

//
// Created by sherman on 18.08.19.
//

#ifndef CPPLEARNING_HASHMAP_H
#define CPPLEARNING_HASHMAP_H

#include <ostream>
#include <initializer_list>
#include <iostream>

using namespace std;

struct Object {
    int id;
    string value;

    Object() = default;

    Object(int id, string value) : id(id), value(std::move(value)) {
        //cout << "constructor1" << endl;
    }

    Object(const Object & object) {
        id = object.id;
        value = object.value;

        //cout << "copy constructor" << endl;
    }

    Object & operator=(const Object & other) {
        //cout << "copy operator" << endl;

        if (this == &other) {
            return *this;
        }

        id = other.id;
        value = other.value;
    }

    Object(Object && other) noexcept {
        //cout << "move constructor" << endl;

        id = other.id;
        value = other.value;

        other.id = 0;
        other.value.clear();
    }

    Object & operator=(Object && other) {
        //cout << "move operator" << endl;

        if (this == &other) {
            return *this;
        }

        id = other.id;
        value = other.value;

        other.id = 0;
        other.value.clear();

        return *this;
    }

    ~Object() {
        //cout << "destructor:" << id << endl;
    }

    bool isEmpty() const {
        return id == -1;
    }
};


class HashMap {
public:
    HashMap() = delete;

    HashMap(const int size);

    // Rules of three
    HashMap(const HashMap & copy);
    HashMap& operator=(const HashMap & copy);
    ~HashMap();

    void set(const Object & value);

    const Object & get(const int id) const;

    int getSize() const;

    int getCapacity() const;

    unsigned int hash(const unsigned int value) const;

private:
    const int MAGIC = 0x9E3779B9;
    const unsigned int MIN_SIZE = 1 << 8;
    const Object EMPTY{-1, ""};

    Object *data_;
    int size_;
    int capacity_;

    void resize();
};


#endif //CPPLEARNING_HASHMAP_H