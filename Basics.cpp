//
// Created by sherman on 04.08.2019.
//
#include <string>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

int main() {
    testing::InitGoogleTest();

    RUN_ALL_TESTS();

    return 0;
}

TEST(BasicsTestSuite, Basics) {
    int p = 1;
    int q = 2;

    int *x = &p;
    int *y = &q;

    cout << *x << endl; // 1
    cout << *y << endl; // 2

    ASSERT_FALSE(p == q);
}
