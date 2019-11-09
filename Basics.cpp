
//
// Created by sherman on 04.08.2019.
//
#include <utility>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <future>
#include "Arguments.h"
#include "MovableType.h"
#include "HashMap.h"
#include "Utils.cpp"
#include "Threads.cpp"

using namespace std;

int main() {
    testing::InitGoogleTest();

    RUN_ALL_TESTS();

    return 0;
}

TEST(BasicsTestSuite, DiffrentPointer) {
    int p = 1;
    int q = 2;

    int *x = &p;
    int *y = &q;

    cout << ::testing::UnitTest::GetInstance()->current_test_info()->name() << endl;
    cout << *x << endl; // 1
    cout << *y << endl; // 2

    ASSERT_FALSE(x == y);
    ASSERT_FALSE(p == q);
}

TEST(BasicsTestSuite, DiffrentPointerWithSameValue) {
    int p = 1;
    int q = 2;

    int *x = &p;
    int *y = &q;

    x = y;

    cout << ::testing::UnitTest::GetInstance()->current_test_info()->name() << endl;
    cout << *x << endl; // 2
    cout << *y << endl; // 2

    ASSERT_TRUE(x == y);
    ASSERT_FALSE(p == q);
}

TEST(BasicsTestSuite, DiffrentReferences) {
    int p = 1;
    int q = 2;

    int & x = p;
    int & y = q;

    cout << ::testing::UnitTest::GetInstance()->current_test_info()->name() << endl;
    cout << x << endl; // 1
    cout << y << endl; // 2

    ASSERT_FALSE(x == y);
    ASSERT_FALSE(p == q);
}

TEST(BasicsTestSuite, DiffrentReferencesWithSameValue) {
    int p = 1;
    int q = 2;

    int & x = p;
    int & y = q;

    x = y;

    cout << ::testing::UnitTest::GetInstance()->current_test_info()->name() << endl;
    cout << x << endl; // 2
    cout << y << endl; // 2

    ASSERT_TRUE(x == y);
    ASSERT_TRUE(p == q);
}

TEST(BasicsTestSuite, Initialization) {
    int p = 1;
    int q = {1};
    auto r = q;
    auto s = 1;
    auto t = &q;
    auto & u = s;

    cout << ::testing::UnitTest::GetInstance()->current_test_info()->name() << endl;

    ASSERT_TRUE(p == q);
    ASSERT_TRUE(q == r);
    ASSERT_TRUE(r == s);
    ASSERT_TRUE(s == *t);
    ASSERT_TRUE(s == u);
}

TEST(BasicsTestSuite, Arguments) {
    std::string text = "text";
    Arguments args(1, text);

    std::string search("ex");
    ASSERT_TRUE(args.hasText(search));
}

TEST(BasicsTestSuite, ArgumentsModifyCopy) {
    std::string text = "text";
    std::vector<int> data = {1, 1, 1, 1, 1};
    Arguments args(1, text);
    vector<int> res = args.modifyCopy(data);
    for (auto elt : res) {
        ASSERT_EQ(elt, -1);
    }

    for (auto elt : data) {
        ASSERT_EQ(elt, 1);
    }
}

TEST(BasicsTestSuite, ArgumentsModify) {
    std::string text = "text";
    std::vector<int> data = {1, 1, 1, 1, 1};
    Arguments args(1, text);
    vector<int> res = args.modify(data);
    for (auto elt : res) {
        ASSERT_EQ(elt, -1);
    }

    for (auto elt : data) {
        ASSERT_EQ(elt, -1);
    }

    ASSERT_NE(&data, &res);
}

TEST(BasicsTestSuite, ArgumentsReturnByRef) {
    std::string text = "text";
    std::vector<int> data = {1, 1, 1, 1, 1};
    Arguments args(1, text);
    auto & res = args.returnByRef(data); // return vector<int>&
    for (auto elt : res) {
        ASSERT_EQ(elt, -1);
    }

    for (auto elt : data) {
        ASSERT_EQ(elt, -1);
    }

    // check res vs data
    for (auto & elt : data) {
        elt = 2;
    }

    for (auto elt : res) {
        ASSERT_EQ(elt, 2);
    }

    ASSERT_EQ(&data, &res);
}

TEST(BasicsTestSuite, MovableTypeCreate) {
    MovableType dataContainer(3);

    ASSERT_EQ(dataContainer.getData().size(), 6);
}

TEST(BasicsTestSuite, MovableTypeConstructor) {
    MovableType dataContainer(100000);
    MovableType another = std::move(dataContainer);

    ASSERT_EQ(another.getData().size(), 200000);
    ASSERT_EQ(dataContainer.getData().size(), 0);
}

TEST(Utils, nextPowerOfTwo) {
    ASSERT_EQ(util::nextPowerOfTwo(15), 16);
    ASSERT_EQ(util::nextPowerOfTwo(16), 16);
    ASSERT_EQ(util::nextPowerOfTwo(4294967295), 0); // max uint
}

TEST(MewPlacement, Arrays) {
    Object expected {10, "test"};

    cout << "init" << endl;

    Object* arr = static_cast<Object *>(::operator new(sizeof(Object) * 2));

    cout << "arr[0]:" << sizeof(arr[0]) << endl;
    cout << "arr[1]:" << sizeof(arr[1]) << endl;

    new(arr + 0) Object(expected);
    new(arr + 1) Object(expected);

    ASSERT_EQ(arr[0].value, expected.value);
    ASSERT_EQ(arr[1].value, expected.value);

    ::operator delete(arr);
}

class ObjectHolder {
public:
    ObjectHolder() {
        data_ = new Object[10];
        size = 10;
    }

    void addByRef(const int index, Object && obj) {
        data_[index] = move(obj);
    }

    const Object & getByRef(const int index) const {
        return data_[index];
    }

    ~ObjectHolder() {
        delete [] data_;
    }

private:
    Object* data_;
    int size;
};


TEST(Object, init) {
    ObjectHolder holder;
    holder.addByRef(0, {10, "test"});
    ASSERT_EQ(holder.getByRef(0).id, 10);

    {
        holder.addByRef(1, {11, "test11"});
    }

    ASSERT_EQ(holder.getByRef(1).id, 11);
    ASSERT_EQ(holder.getByRef(1).value, "test11");

    Object object {12, "test12"};
    holder.addByRef(3, move(object));

    ASSERT_EQ(holder.getByRef(3).id, 12);
    ASSERT_EQ(holder.getByRef(3).value, "test12");

    // wiped out
    ASSERT_EQ(object.id, 0);
    ASSERT_EQ(object.value, "");
}

TEST(HashMap, GetSize) {
    HashMap map(10);
    ASSERT_EQ(map.getSize(), 0);
    map.set({10, "test"});
    ASSERT_EQ(map.getSize(), 1);
}

TEST(HashMap, GetMaxSize) {
    HashMap map(10);
    ASSERT_EQ(map.getCapacity(), 256); // min size
}

TEST(HashMap, hash) {
    HashMap map(10);
    ASSERT_EQ(map.hash(2), 60);
    ASSERT_EQ(map.hash(500), 4);
    ASSERT_EQ(map.hash(1000), 8);
    ASSERT_EQ(map.hash(1001), 166);
}

TEST(HashMap, set) {
    HashMap map(10);
    map.set({10, "test"});
    Object expected = {10, "test"};
    ASSERT_EQ(map.get(10).id, expected.id);
    ASSERT_EQ(map.get(10).value, expected.value);
    ASSERT_EQ(map.get(1).id, -1);

    ASSERT_EQ(map.get(10).id, expected.id);
    ASSERT_EQ(map.get(10).value, expected.value);
    ASSERT_EQ(map.get(1).id, -1);

    // rewrite
    map.set({10, "rewritten"});
    ASSERT_EQ(map.get(10).value, "rewritten");
}

TEST(HashMap, empty) {
    HashMap map(10);
    ASSERT_EQ(map.get(1).id, map.get(2).id);
}

TEST(HashMap, fill) {
    HashMap map(256);
    for (int i = 0; i < 256; i++) {
        map.set({i, string("test").append(to_string(i))});
    }

    for (int i = 0; i < 256; i++) {
        ASSERT_EQ(map.get(i).id, i);
        ASSERT_EQ(map.get(i).value, string("test").append(to_string(i)));
    }
}

TEST(ForLoops, modernFor) {
    int numbers[] {1, 2, 3};

    vector<int> actual;

    for (auto && number : numbers) {
        actual.push_back(number);
    }

    ASSERT_EQ(actual[0], numbers[0]);
    ASSERT_EQ(actual[1], numbers[1]);
    ASSERT_EQ(actual[2], numbers[2]);

    actual.clear();
    for (auto number : numbers) {
        actual.push_back(number);
    }

    ASSERT_EQ(actual[0], numbers[0]);
    ASSERT_EQ(actual[1], numbers[1]);
    ASSERT_EQ(actual[2], numbers[2]);
}

TEST(Threads, promise) {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::thread th(threads::initializer, &promise);
    ASSERT_EQ(future.get(), 42);
    th.join();
}

TEST(Threads, blocking) {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::thread th(threads::blocking, &promise);
    ASSERT_EQ(future.get(), 42);
    th.join();
}