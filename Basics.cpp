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
    cout << *x << endl; // 1
    cout << *y << endl; // 1

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
    cout << x << endl; // 1
    cout << y << endl; // 1

    ASSERT_TRUE(x == y);
    ASSERT_TRUE(p == q);
}


