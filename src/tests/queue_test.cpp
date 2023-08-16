#include <gtest/gtest.h>
#include <queue>
#include "../s21_containers.h"

TEST(queue_test, push_pop) {
    s21::queue<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    std::queue<int> b;
    b.push(1);
    b.push(2);
    b.push(3);
    EXPECT_EQ(a.front(), b.front());
    EXPECT_EQ(a.back(), b.back());
    a.pop();
    a.pop();
    b.pop();
    b.pop();
    EXPECT_EQ(a.back(), b.back());
    a.pop();
    b.pop();
    EXPECT_TRUE(a.empty());

    auto test = std::move(a);
    s21::queue<int> c;
    c.push(1);
    c.push(2);
    c.push(3);
    a = c;
    EXPECT_EQ(a.front(), 1);
    EXPECT_EQ(a.back(), 3);


}

TEST(queue_test, test) {
    s21::queue<int> a{1, 2, 3};
    s21::queue<int> a2{1, 2, 3};
    s21::queue<int> a3{1, 2, 3};
    s21::queue<int> c = a;
    s21::queue<int> d;
    const s21::queue<int> test_const{1, 2, 3};
    EXPECT_EQ(test_const.front(), 1);
    EXPECT_EQ(test_const.back(), 3);
    d.swap(a3);
    d = std::move(a2);
    auto it = a.size();
    EXPECT_EQ(3, it);
    s21::queue<int> b;
    auto it2 = b.size();
    EXPECT_EQ(0, it2);
}

TEST(queue_test, size) {
    s21::queue<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);
    auto it = a.size();
    EXPECT_EQ(5, it);
    s21::queue<int> b;
    auto it2 = b.size();
    EXPECT_EQ(0, it2);
}

TEST(queue_test, emplace_back) {
    s21::queue<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    a.emplace_back(1, 1, 2, 5, 6);
    auto it = a.size();
    EXPECT_EQ(8, it);
    EXPECT_EQ(a.front(), 1);
    EXPECT_EQ(a.back(), 6);
}
