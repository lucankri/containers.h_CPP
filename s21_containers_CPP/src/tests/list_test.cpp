#include "../s21_containers.h"
#include <gtest/gtest.h>
#include <list>

TEST(list_test, front) {
  s21::list<int> a = {1, 2, 3};
  std::list<int> b = {1, 2, 3};
  auto it1 = a.front();
  auto i = b.front();
  ASSERT_EQ(it1, i);
}

TEST(list_test, size) {
  s21::list<int> a = {1, 2, 3, 5, 6};
  s21::list<int> b(5);
  s21::list<int> c = a;
  auto a1 = a.size();
  ASSERT_EQ(a1, 5);
  s21::list<int> d = {1, 2, 3, 5, 6, 9, 0};
  d = a;
  s21::list<int> test1 = {1, 2, 3, 5, 6};
  s21::list<int> test2(5);
  test1 = test2;
  ASSERT_EQ(test1.size(), test2.size());
}

TEST(list_test, size2) {
  s21::list<int> a;
  auto a1 = a.size();
  ASSERT_EQ(a1, 0);
}

TEST(list_test, is_empty_true) {
  s21::list<int> a;
  auto a1 = a.empty();
  ASSERT_TRUE(a1);
}

TEST(list_test, is_empty_false) {
  s21::list<int> a = {1, 23, 43};
  auto a1 = a.empty();
  ASSERT_FALSE(a1);
}

TEST(list_test, back) {
  s21::list<int> a = {1, 23, 43, 3};
  auto a1 = a.back();
  ASSERT_EQ(a1, 3);
}

TEST(list_test, back2) {
  s21::list<int> a = {};
  auto a1 = a.back();
  ASSERT_EQ(a1, 0);
}

TEST(list_test, push_front1) {
  s21::list<int> a = {};
  a.push_front(1);
  a.push_front(3);
  a.push_front(5);
  std::list<int> b = {5, 3, 1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    ASSERT_EQ(*it, *i);
    ++i;
  }
}

TEST(list_test, push_front2) {
  s21::list<int> a = {};
  a.push_front(1);
  a.push_front(3);
  a.push_front(5);
  a.push_front(5);
  a.push_front(5);
  std::list<int> b = {5, 5, 5, 3, 1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    ASSERT_EQ(*it, *i);
    ++i;
  }
}

TEST(list_test, push_back_1_pop) {
  s21::list<int> a = {};
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  std::list<int> b = {1, 2, 3};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    ASSERT_EQ(*it, *i);
    ++i;
  }
  a.pop_back();
  b = {1, 2};
  auto it3 = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    ASSERT_EQ(*it, *it3);
    ++it3;
  }
}

TEST(list_test, push_back_2_pop) {
  s21::list<int> a;
  a.push_back(1);
  std::list<int> b = {1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    ASSERT_EQ(*it, *i);
    ++i;
  }
  a.pop_back();
  ASSERT_EQ(a.empty(), true);
}

TEST(list_test, pop_front) {
  s21::list<int> a;
  a.push_front(1);
  a.push_front(321);
  a.pop_front();
  s21::list<int> b = {1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    ASSERT_EQ(*it, *i);
    ++i;
  }
}

TEST(list_test, swap) {
  s21::list<int> a1 = {0, 2, 4, 6};
  s21::list<int> a2 = {6, 4, 2, 0};
  a1.swap(a2);
  std::list<int> a3 = {0, 2, 4, 6};
  std::list<int> a4 = {6, 4, 2, 0};
  a4.swap(a3);
  auto it_original = a3.begin();
  for (auto it = a1.begin(); it != a1.end(); ++it) {
    EXPECT_EQ(*it_original, *it);
    it_original++;
  }
}

TEST(list_test, reverse) {
  s21::list<int> a1 = {0, 2, 4, 6};
  std::list<int> a2 = {0, 2, 4, 6};
  a1.reverse();
  a2.reverse();
  auto it = a1.begin();
  for (auto it_original = a2.begin(); it_original != a2.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it);
    it++;
  }
}

TEST(list_test, max_size) {
  s21::list<int> a1;
  std::list<int> a2;
  EXPECT_EQ(a1.max_size(), a2.max_size());
}

TEST(tests_of_List, unique_1) {
  s21::list<int> a = {0, 1, 254, 333, 333, 12, 1};
  std::list<int> b = {0, 1, 254, 333, 333, 12, 1};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, unique_2) {
  s21::list<int> a = {0, 0, 0, 0, 0, 0};
  std::list<int> b = {0, 0, 0, 0, 0, 0};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, unique_3) {
  s21::list<int> a = {5, 4, 3, 2, 1, 5};
  std::list<int> b = {5, 4, 3, 2, 1, 5};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, insert_1) {
    s21::list<int> a = {-1, 0, 2};
    std::list<int> b = {-1, 0, 2};
    auto i = a.begin();
    auto it_std = b.begin();
    auto it_std_2 = a.insert(i, -2);
    auto i2 = b.insert(it_std, -2);
    ASSERT_EQ(*it_std_2, *i2);

}

TEST(list_test, merge) {
  s21::list<int> a = {1, 5, 7};
  s21::list<int> b = {2, 2, 4};
  s21::list<int> res = {1, 2, 2, 4, 5, 7};
  a.merge(b);

  auto it = a.begin();
  for (auto i = res.begin(); i != res.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }

  EXPECT_EQ(res.size(), a.size());
  EXPECT_EQ(b.empty(), true);
}

TEST(list_test, sort_1) {
  s21::list<int> a = {100000, 43, 2, 3, 41, -11, 3, 0, 32};
  std::list<int> b = {100000, 43, 2, 3, 41, -11, 3, 0, 32};
  a.sort();
  b.sort();
  auto it = b.begin();
  for (auto i = a.begin(); i != a.end(); i++) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, sort_2) {
  s21::list<int> a = {1, 1, 1, 1};
  std::list<int> b = {1, 1, 1, 1};
  a.sort();
  b.sort();
  auto it = b.begin();
  for (auto i = a.begin(); i != a.end(); i++) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, sort_3) {
  s21::list<int> a = {5, 8, 1, 4, 2, 3, 6, 7, 0};
  a.sort();
  auto it = a.begin();
  for (int i = 0; i < 9; ++i, ++it) {
    EXPECT_EQ(*it, i);
  }
}

TEST(list_test, erase_1) {
  s21::list<int> a = {10, 10, 20, 30, 40, 50, 60};
  s21::list<int>::iterator it = a.begin();

  a.erase(it);
  auto i = a.begin();
  int j = 10;
  size_t size = 0;
  while (size < a.size()) {
    ASSERT_EQ(j, *i);
    j += 10;
    i++, size++;
  }
}


TEST(list_test, splice) {
    s21::list<int> a = {0, 1, 3};
    s21::list<int> b = {4, 5};
    auto i = a.begin();
    ++i;
    ++i;
    ++i;
    a.splice(i, b);
    auto it = a.begin();

    std::list<int> a1 = {0, 1, 3};
    std::list<int> b1 = {4, 5};
    auto i_res = a1.begin();
    ++i_res;
    ++i_res;
    ++i_res;
    a1.splice(i_res, b1);


    for (auto it_res = a1.begin(); it_res != a1.end(); it_res++, it++) {
        EXPECT_EQ(*it, *it_res);
    }

}


TEST(list_test, emplace_front) {
  s21::list<int> a = {6, 7, 8};
  a.emplace_front(1, 2, 3, 4, 5);
  auto it = a.begin();
  for (int i = 1; i <= 8; i++, ++it) {
    EXPECT_EQ(*it, i);
  }
  
  EXPECT_FALSE(a.begin() == a.end());
  it--;
  it--;
  EXPECT_EQ(*it, 7);
}

TEST(list_test, const_list) {
  const s21::list<int> a = {1, 2, 3};
  auto it = a.begin();
  auto it2 = a.begin();
  it--;
  it++;
  --it;
  EXPECT_FALSE(*it == *it2);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 3);

}

TEST(list_test, emplace_back_1) {
    s21::list<int> a = {1, 2, 3, 4};
    a.emplace_back(1, 1, 2, 5, 6);
    auto it = a.size();
    EXPECT_EQ(9, it);
    EXPECT_EQ(a.front(), 1);
    EXPECT_EQ(a.back(), 6);
}


TEST(list_test, constructor_move) {
    s21::list<int> a = {1, 2, 3, 4};
    s21::list<int> b = std::move(a);
    EXPECT_FALSE(a.begin() != a.end());
}

TEST(list_test, operator_copy) {
    s21::list<int> a = {1, 2, 3, 4};
    s21::list<int> b = {1, 2};
    b = a;
    EXPECT_EQ(b.size(), 4);
}
