#include "../s21_containers.h"
#include "gtest/gtest.h"
#include <stack>

TEST(stack_test, size) {
  s21::stack<int> a;
  a.push(3);
  auto size = a.size();
  ASSERT_EQ(1, size);

  s21::stack<int> b;
  auto size_2 = b.size();
  ASSERT_EQ(0, size_2);
}

TEST(stack_test, test) {
  s21::stack<int> a{1, 2, 4};
  a.push(3);
  auto size = a.size();
  ASSERT_EQ(4, size);
  s21::stack<int> c = a;
  ASSERT_EQ(c.size(), a.size());
  s21::stack<int> d = std::move(a);
  ASSERT_EQ(0, a.size());
  s21::stack<int> b;
  auto size_2 = b.size();
  ASSERT_EQ(0, size_2);
  s21::stack<int> test1;
  test1 = std::move(d);
  ASSERT_EQ(0, d.size());
}

TEST(stack_test, test2) {
  s21::stack<int> a {1, 2, 4, 5, 6, 7};
  s21::stack<int> b;
  b = std::move(a);
  ASSERT_EQ(a.size(), 0);
  
}


TEST(stack_test, push_and_pop) {
  s21::stack<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  a.push(4);
  a.push(5);
  int i = 5;
  size_t size = 1;
  while (size <= a.size()) {
    ASSERT_EQ(i, a.top());
    a.pop();
    i--;
    size++;
  }
  a.pop();
  a.pop();
  a.push(1);
  a.push(2);
  a.push(3);
  i = 3;
  size = 1;
  while (size <= a.size()) {
    ASSERT_EQ(i, a.top());
    a.pop();
    i--;
    size++;
  }
}

TEST(stack_test, push_and_pop_2) {
  s21::stack<int> a;
  a.pop();
  auto it = a.top();
  ASSERT_EQ(it, 0);
  ASSERT_EQ(a.empty(), true);
}

TEST(stack_test, top) {
  s21::stack<int> a;
  a.push(3);
  a.push(33);
  a.push(333);
  auto it = a.top();
  ASSERT_EQ(333, it);
  a.pop();
  it = a.top();
  ASSERT_EQ(33, it);
}

TEST(stack_test, eq) {
  s21::stack<int> a;
  s21::stack<int> b;
  a.push(11);
  a.push(22);
  a.push(33);
  b = a;
  size_t size = 1;
  while (size <= a.size()) {
    ASSERT_EQ(b.top(), a.top());
    a.pop();
    b.pop();
    size++;
  }
}

TEST(stack_test, swap) {
  s21::stack<int> a;
  s21::stack<int> b;
  a.push(5);
  a.push(4);
  a.push(3);
  a.push(2);
  a.push(1);
  a.swap(b);
  size_t size = b.size();
  for (size_t i = 1; i <= size; i++) {
    EXPECT_EQ(b.top(), i);
    b.pop();
  }
  EXPECT_EQ(b.empty(), true);
}
