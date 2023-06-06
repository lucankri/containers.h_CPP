#include <gtest/gtest.h>
#include "../s21_containersplus.h"
#include <set>

auto test1 = {'1', '2', '3', '4', '5'};
auto test2 = {'1', '2', '3', '4', '5'};

TEST(multiset_test, constructor_1) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test2;
    auto it1 = multiset1.begin();
    EXPECT_EQ(multiset1.size(), multiset2.size());
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_2) {
    s21::multiset<char> multiset1 = {'1', '2', '3'};
    std::multiset<char> multiset2 = {'1', '2', '3'};
    auto it1 = multiset1.begin();
    EXPECT_EQ(multiset1.size(), multiset2.size());
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_3) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test1;
    EXPECT_EQ(multiset1.size(), multiset2.size());
    auto it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_4) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test1;
    auto a = multiset1;
    auto b = multiset2;
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    EXPECT_EQ(a.size(), b.size());
    it1 = multiset1.begin();
    EXPECT_EQ(multiset1.size(), multiset2.size());
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_5) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test2;
    auto a = multiset1;
    auto b = multiset2;
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    EXPECT_EQ(a.size(), b.size());
    it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multiset_test, constructor_6) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test1;
    auto a = std::move(multiset1);
    auto b = std::move(multiset2);
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
    EXPECT_EQ(a.size(), b.size());
    it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
    EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multiset_test, constructor_7) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test2;
    auto a = std::move(multiset1);
    auto b = std::move(multiset2);
    auto it1 = a.begin();
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(multiset1.size(), multiset2.size());

    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}


TEST(multiset_test, constructor_8) {
    s21::multiset<std::string> multiset1 = {"test", "cases", "hello"};
    std::multiset<std::string> multiset2 = {"test", "cases", "hello"};
    auto it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, begin) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test1;
    auto it1 = multiset1.begin();
    auto it2 = multiset2.begin();
    EXPECT_EQ(*it1, *it2);
}


TEST(multiset_test, end) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test1;
    auto it1 = multiset1.end();
    auto it2 = multiset2.end();
    it1--;
    it2--;
    EXPECT_EQ(*it1, *it2);
}


TEST(multiset_test, empty) {
    s21::multiset<char> multiset1;
    std::multiset<char> multiset2;
    EXPECT_EQ(multiset1.empty(), multiset2.empty());
    s21::multiset<char> multiset3 = test1;
    std::multiset<char> multiset4 = test1;
    EXPECT_EQ(multiset4.empty(), multiset3.empty());
    multiset3.clear();
    multiset4.clear();
    EXPECT_EQ(multiset3.empty(), multiset4.empty());

}

TEST(multiset_test, insert) {
    s21::multiset<char> multiset1;
    std::multiset<char> multiset2;
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(*(multiset1.insert(i)), *(multiset2.insert(i)));
    }
    EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multiset_test, size) {
    s21::multiset<char> multiset1;
    std::multiset<char> multiset2;
    s21::multiset<char> multiset3 = test1;
    std::multiset<char> multiset4 = test1;
    EXPECT_EQ(multiset1.size(), multiset2.size());
    EXPECT_EQ(multiset3.size(), multiset4.size());
    multiset3.clear();
    multiset4.clear();
    EXPECT_EQ(multiset3.size(), multiset4.size());

}


TEST(multiset_test, clear) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test1;
    multiset1.clear();
    multiset2.clear();
    EXPECT_EQ(multiset1.empty(), multiset2.empty());
}

TEST(multiset_test, clear2) {
    s21::multiset<char> multiset1;
    std::multiset<char> multiset2;
    multiset1.clear();
    multiset2.clear();
    EXPECT_EQ(multiset1.empty(), multiset2.empty());
}


TEST(multiset_test, init_1) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 1, 1, 20};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 1, 1, 20};

  ASSERT_EQ(*v.begin(), *vc.begin());
  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
}

TEST(multiset_test, init_2) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 1, 1, 20};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 1, 1, 20};
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}


TEST(multiset_test, insert_erase) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  std::multiset<double> vc = {2,  -3, 20, -5, 1, -6, 8, 42,
                              26, 1,  1,  1,  8, 8,  8};
  v.insert(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset_test, lower_bound) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1};
  s21::multiset<double>::iterator x = v.lower_bound(8);
  --x;
  ASSERT_EQ(*x, 2);
}

TEST(multiset_test, emplace_4) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6};
  v.emplace(8, 42, 26, 1, 1, 1);
  s21::multiset<double>::iterator x = v.lower_bound(8);
  --x;
  ASSERT_EQ(*x, 2);
}

TEST(multiset_test, rand) {
  s21::multiset<double> v;
  for (int i = 0; i <= 10000; i++) {
      v.insert(rand() % 1001);
  }

  for (int i = 0; i <= 10000; i++) {
      auto it = v.find(rand() % 1001);
      v.erase(it);
  }
  EXPECT_EQ(v.size(), v.size());
  
}

TEST(multiset_test, upper_bound) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  auto x = v.upper_bound(8);
  --x;
  ASSERT_EQ(*x, 8);
}

TEST(multiset_test, equal_range) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  auto x = v.equal_range(8);
  ASSERT_EQ(*x.first, 8);
  ASSERT_EQ(*x.second, 20);
}

TEST(multiset_test, cont) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  EXPECT_EQ(v.count(1), 4);
}

TEST(multiset_test, find4) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  EXPECT_EQ(*(v.find(1)), 1);
}

TEST(multiset_test, contains) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  EXPECT_EQ(v.contains(1), true);
}


TEST(multiset_test, swap_3) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::multiset<double> v1 = {100, 200, 300, 400, 500};
  std::multiset<double> vc1 = {100, 200, 300, 400, 500};
  v.swap(v1);
  vc.swap(vc1);
  v.max_size();

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    EXPECT_EQ(*x, *y);
  }
}

TEST(multiset_test, merge_4) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::multiset<double> v1 = {100, 200, 300, 400, 500};
  s21::multiset<double> vc = {-3, 1,  -5,  42,  2,   -6,  8,
                              20, 26, 100, 200, 300, 400, 500};
  v.merge(v1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset_test, operator_eq) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::multiset<double> v1 = {100, 200, 300, 400, 500};
  v1 = v;
  auto x = v.begin();
  auto y = v1.begin();
  for (; x != v.end(); ++x, ++y) {
    EXPECT_EQ(*x, *y);
  }
}

TEST(multiset_test, operator_eq_move) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::multiset<double> v1 = {100, 200, 300, 400, 500};
  v = std::move(v1);
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(*(v.find(100)), 100);
  EXPECT_EQ(*(v.find(200)), 200);
  EXPECT_EQ(*(v.find(300)), 300);
  EXPECT_EQ(*(v.find(400)), 400);
  EXPECT_EQ(*(v.find(500)), 500);
  
}


TEST(multiset_test, insert3) {
    s21::multiset<char> multiset1 = test1;
    std::multiset<char> multiset2 = test1;
    for (int i = 0; i < 5; i++) {
        multiset1.insert(i);
        multiset2.insert(i);
    }
    auto it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    EXPECT_EQ(multiset1.size(), multiset2.size());
}

// TEST(multiset_test, erase2) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     EXPECT_EQ(multiset1.size(), multiset2.size());
//     auto it1 = multiset1.begin();
//     auto it2 = multiset2.begin();
//     multiset1.erase(it1);
//     multiset2.erase(it2);
//     it1 = multiset1.begin();
//     it2 = multiset2.begin();
//     for (; it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
//     EXPECT_EQ(multiset1.size(), multiset2.size());
// }

// TEST(multiset_test, erase3) {  // exc leak
//     s21::multiset<char> multiset1 = test1;
//     EXPECT_ANY_THROW(multiset1.erase(multiset1.end()));
// }

// TEST(multiset_test, swap1) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     s21::multiset<char> a;
//     std::multiset<char> b;
//     multiset1.swap(a);
//     multiset2.swap(b);
//     EXPECT_EQ(multiset1.size(), multiset2.size());
//     EXPECT_EQ(a.size(), b.size());
//     auto it1 = multiset1.begin();
//     auto it11 = a.begin();
//     auto it2 = multiset2.begin();
//     auto it22 = b.begin();
//     for (; it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
//     for (; it22 != b.end(); it11++, it22++) EXPECT_EQ(*it11, *it22);
// }

// TEST(multiset_test, swap2) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     s21::multiset<char> a = test2;
//     std::multiset<char> b = test2;
//     multiset1.swap(a);
//     multiset2.swap(b);
//     EXPECT_EQ(multiset1.size(), multiset2.size());
//     EXPECT_EQ(a.size(), b.size());
//     auto it1 = multiset1.begin();
//     auto it11 = a.begin();
//     auto it2 = multiset2.begin();
//     auto it22 = b.begin();
//     for (; it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
//     for (; it22 != b.end(); it11++, it22++) EXPECT_EQ(*it11, *it22);
// }

// TEST(multiset_test, merge1) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     s21::multiset<char> a = test2;
//     std::multiset<char> b = test2;
//     multiset1.merge(a);
//     multiset2.merge(b);
//     auto it1 = multiset1.begin();
//     for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
// }

// TEST(multiset_test, merge2) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     s21::multiset<char> a;
//     std::multiset<char> b;
//     multiset1.merge(a);
//     multiset2.merge(b);
//     auto it1 = multiset1.begin();
//     for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
// }

// TEST(multiset_test, count1) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     EXPECT_EQ(multiset1.count(1), multiset2.count(1));
//     EXPECT_EQ(multiset1.count(2), multiset2.count(2));
//     EXPECT_EQ(multiset1.count(6), multiset2.count(6));
// }

// TEST(multiset_test, count2) {
//     s21::multiset<char> multiset1;
//     std::multiset<char> multiset2;
//     EXPECT_EQ(multiset1.count(1), multiset2.count(1));
//     EXPECT_EQ(multiset1.count(2), multiset2.count(2));
//     EXPECT_EQ(multiset1.count(6), multiset2.count(6));
// }

// TEST(multiset_test, count3) {
//     s21::multiset<char> multiset1 = {1, 1, 1, 1, 1, 1, 1, 1};
//     std::multiset<char> multiset2 = {1, 1, 1, 1, 1, 1, 1, 1};
//     EXPECT_EQ(multiset1.count(1), multiset2.count(1));
//     EXPECT_EQ(multiset1.count(2), multiset2.count(2));
//     EXPECT_EQ(multiset1.count(6), multiset2.count(6));
// }

// TEST(multiset_test, find1) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     EXPECT_EQ(*(multiset1.find(1)), *(multiset2.find(1)));
//     EXPECT_EQ(*(multiset1.find(2)), *(multiset2.find(2)));
//     EXPECT_EQ(*(multiset1.find(6)), *(multiset2.find(6)));
// }

// TEST(multiset_test, find2) {
//     s21::multiset<char> multiset1;
//     EXPECT_EQ(multiset1.find(1).base(), multiset1.end().base());
//     EXPECT_EQ(multiset1.find(2).base(), multiset1.end().base());
//     EXPECT_EQ(multiset1.find(6).base(), multiset1.end().base());
// }

// TEST(multiset_test, find3) {
//     s21::multiset<char> multiset1 = {1, 1, 1, 1, 1, 1, 1, 1};
//     std::multiset<char> multiset2 = {1, 1, 1, 1, 1, 1, 1, 1};
//     EXPECT_EQ(*(multiset1.find(1)), *(multiset2.find(1)));
// }

// TEST(multiset_test, contains1) {
//     s21::multiset<char> multiset1 = test1;
//     EXPECT_EQ(multiset1.contains(1), true);
//     EXPECT_EQ(multiset1.contains(2), true);
//     EXPECT_EQ(multiset1.contains(6), true);
// }

// TEST(multiset_test, contains2) {
//     s21::multiset<char> multiset1;
//     EXPECT_EQ(multiset1.contains(1), false);
//     EXPECT_EQ(multiset1.contains(2), false);
//     EXPECT_EQ(multiset1.contains(6), false);
// }

// TEST(multiset_test, contains3) {
//     s21::multiset<char> multiset1 = {1, 1, 1, 1, 1, 1, 1, 1};
//     std::multiset<char> multiset2 = {1, 1, 1, 1, 1, 1, 1, 1};
//     EXPECT_EQ(multiset1.contains(1), true);
//     EXPECT_EQ(multiset1.contains(2), false);
//     EXPECT_EQ(multiset1.contains(6), false);
// }

// TEST(multiset_test, equal_range1) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     auto pair1 = multiset1.equal_range(9);
//     auto pair2 = multiset2.equal_range(9);
//     EXPECT_EQ(*(pair1.first), *(pair2.first));
//     EXPECT_EQ(*(pair1.second), *(pair2.second));
//     pair1 = multiset1.equal_range(1);
//     pair2 = multiset2.equal_range(1);
//     EXPECT_EQ(*(pair1.first), *(pair2.first));
//     EXPECT_EQ(*(pair1.second), *(pair2.second));
//     pair1 = multiset1.equal_range(2);
//     pair2 = multiset2.equal_range(2);
//     EXPECT_EQ(*(pair1.first), *(pair2.first));
//     EXPECT_EQ(*(pair1.second), *(pair2.second));
// }

// TEST(multiset_test, equal_range2) {
//     s21::multiset<char> multiset1;
//     auto pair1 = multiset1.equal_range(9);
//     EXPECT_EQ(pair1.first.base(), multiset1.end().base());
//     EXPECT_EQ(pair1.second.base(), multiset1.end().base());
//     pair1 = multiset1.equal_range(1);
//     EXPECT_EQ(pair1.first.base(), multiset1.end().base());
//     EXPECT_EQ(pair1.second.base(), multiset1.end().base());
//     pair1 = multiset1.equal_range(2);
//     EXPECT_EQ(pair1.first.base(), multiset1.end().base());
//     EXPECT_EQ(pair1.second.base(), multiset1.end().base());
// }

// TEST(multiset_test, lower_bound1) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     auto it1 = multiset1.lower_bound(9);
//     auto it2 = multiset2.lower_bound(9);
//     EXPECT_EQ(*(it1), *(it2));
//     it1 = multiset1.lower_bound(1);
//     it2 = multiset2.lower_bound(1);
//     EXPECT_EQ(*(it1), *(it2));
//     it1 = multiset1.lower_bound(2);
//     it2 = multiset2.lower_bound(2);
//     EXPECT_EQ(*(it1), *(it2));
// }

// TEST(multiset_test, upper_bound1) {
//     s21::multiset<char> multiset1 = test1;
//     std::multiset<char> multiset2 = test1;
//     auto it1 = multiset1.upper_bound(9);
//     auto it2 = multiset2.upper_bound(9);
//     EXPECT_EQ(*(it1), *(it2));
//     it1 = multiset1.upper_bound(1);
//     it2 = multiset2.upper_bound(1);
//     EXPECT_EQ(*(it1), *(it2));
//     it1 = multiset1.upper_bound(2);
//     it2 = multiset2.upper_bound(2);
//     EXPECT_EQ(*(it1), *(it2));
// }

// TEST(multiset_test, emplace) {
//     struct structure {
//         int x_;
//         long double y_;
//         char z_;
//         bool operator==(const structure &other) const {
//             return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
//         }
//         bool operator>(const structure &other) const { return x_ > other.x_; }
//         bool operator<(const structure &other) const { return x_ < other.x_; }
//         bool operator>=(const structure &other) const { return x_ >= other.x_; }
//         bool operator<=(const structure &other) const { return x_ <= other.x_; }
//         structure() {
//             x_ = 0;
//             y_ = 0;
//             z_ = 0;
//         }
//         structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
//     };
//     const structure elem1 = {6, 7., '8'};
//     const structure elem2 = {7, 8., '9'};
//     const structure expecting_result = {1, 2., '3'};
//     std::initializer_list<structure> a = {elem1, elem2};
//     s21::multiset<structure> set1(a);
//     auto v1 = set1.emplace(1, 2., '3');
//     auto it_res = set1.begin();
//     EXPECT_TRUE(*it_res == expecting_result);
//     ++it_res;
//     EXPECT_TRUE(*it_res == elem1);
//     ++it_res;
//     EXPECT_TRUE(*it_res == elem2);
//     EXPECT_EQ(v1.at(0).second, true);
// }

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }

