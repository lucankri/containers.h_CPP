#include "../s21_containers.h"
#include <gtest/gtest.h>
#include <vector>

TEST(vector_test, at_throw) {
    const s21::vector<int> v;
    ASSERT_ANY_THROW(v.at(3));
}

TEST(vector_test, front_throw) {
    const s21::vector<int> v;
    ASSERT_ANY_THROW(v.front());
}


TEST(vector_test, back_throw) {
    const s21::vector<int> v;
    ASSERT_ANY_THROW(v.back());
}

TEST(vector_test, shrink_to_fit_capacity) {
    s21::vector<int> v = {1, 2, 3};
    v.shrink_to_fit();
    ASSERT_EQ(v.capacity(), 3);
}

TEST(vector_test, insert_throw) {
    s21::vector<int> v = {1, 2, 3};
    auto it_end = v.end();
    ++it_end;
    int value = 5;
    ASSERT_ANY_THROW(v.insert(it_end, value));
}

TEST(vector_test, swap) {
    s21::vector<int> v1 = {1, 2, 3};
    s21::vector<int> v2 = {10, 11, 12};
    v1.swap(v2);
    ASSERT_EQ(v1[0], 10);
    ASSERT_EQ(v1[1], 11);
    ASSERT_EQ(v1[2], 12);

    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
    ASSERT_EQ(v2[2], 3);
}

TEST(vector_test, is_data) {
    s21::vector<int> a2 = {1};
    EXPECT_EQ(a2.data() == nullptr, false);

    s21::vector<int> a1;
    EXPECT_EQ(a1.data(), nullptr);
}

TEST(vector_test, test) {
    s21::vector<int> a2(4);
    EXPECT_EQ(a2.size(), 4);
    s21::vector<int> a1 = a2;
    s21::vector<int> a3 = std::move(a1);
    s21::vector<int> a4;
    a4 = a3;

    const s21::vector<int> a_test = {1,2,3};
    EXPECT_EQ(a_test.front(), 1);
    EXPECT_EQ(a_test.back(), 3);
    EXPECT_EQ(*(a_test.data()), 1);
    EXPECT_EQ(a_test[2], 3);
    EXPECT_EQ(a1.data(), nullptr);
}

TEST(vector_test, front_back) {
    s21::vector<int> a = {0, 1, 2, 3};
    std::vector<int> b = {0, 1, 2, 3};
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.front(), b.front());
    EXPECT_EQ(a.back(), b.back());

    s21::vector<int> a1;
    std::vector<int> b1;
    try {
        EXPECT_EQ(a1.size(), b1.size());
        EXPECT_EQ(a1.front(), b1.front());
    } catch (std::out_of_range &error) {
        EXPECT_EQ(error.what(), std::string("s21::vector::front: Using methods on a zero sized container"));
    }
}
TEST(vector_test, front_back_ex) {
    s21::vector<int> a1;
    std::vector<int> b1;
    try {
        EXPECT_EQ(a1.back(), b1.back());
    } catch (std::out_of_range &error){
        EXPECT_EQ(error.what(), std::string("s21::vector::front: Using methods on a zero sized container"));
    }
}

TEST(vector_test, at) {
    s21::vector<int> a = {0, 1, 2};
    const s21::vector<int> a1 = {0, 1, 2};
    EXPECT_EQ(a1.at(0), 0);
    std::vector<int> orig = {0, 1, 2};
    for (size_t i = 0; i < a.size(); i++) {
        EXPECT_EQ(a.at(i), orig.at(i));
    }
    EXPECT_EQ(a.capacity(), orig.capacity());
    EXPECT_EQ(a.size(), orig.size());

    try {
        a.at(-1);
    }
    catch (std::out_of_range &error){
        EXPECT_EQ(error.what(), std::string("s21::vector::at: The index is out of range"));
    }

    try {
        a.at(5);
    }
    catch (std::out_of_range &error){
        EXPECT_EQ(error.what(), std::string("s21::vector::at: The index is out of range"));
    }

}

TEST(vector_vector_test, begin) {
    s21::vector<int> a1 = {-1, 0, 4, 8};
    std::vector<int> b1 = {-1, 0, 4, 8};
    auto it1 = a1.begin();
    auto it2 = b1.begin();
    EXPECT_EQ(*it1, *it2);
    EXPECT_EQ(a1.capacity(), b1.capacity());
    EXPECT_EQ(a1.size(), b1.size());
}


TEST(vector_vector_test, end) {
    s21::vector<int> a1 = {-1, 0, 4, 8};
    std::vector<int> b1 = {-1, 0, 4, 8};

    auto it1 = a1.end() - 1;
    auto it2 = b1.end() - 1;
    EXPECT_EQ(*it1, *it2);

    EXPECT_EQ(a1.capacity(), b1.capacity());
    EXPECT_EQ(a1.size(), b1.size());
}

TEST(vector_test, push_back) {
    s21::vector<int> a1 = {-1, 0, 4, 8};
    std::vector<int> b1 = {-1, 0, 4, 8};
    int a = 3;
    a1.push_back(a);
    b1.push_back(a);
    EXPECT_EQ(a1[4], b1[4]);
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
}

TEST(vector_test, emplace) {
    s21::vector<int> v1 = {0, 1, 2, 7, 8};
    auto it = v1.begin();
    ++it;
    ++it;
    ++it;
    v1.emplace(it, 3, 4, 5, 6);

    for (size_t i = 0; i < 9; i++) {
        EXPECT_EQ(v1[i], i);
    }

}

TEST(vector_test, emplace_back) {
    s21::vector<int> v1 = {0, 1, 2};
    auto it = v1.begin();
    ++it;
    ++it;
    ++it;
    v1.emplace_back(3, 4, 5, 6);

    for (size_t i = 0; i < 6; i++) {
        EXPECT_EQ(v1[i], i);
    }

}

TEST(vector_test, pop_back) {
    s21::vector<int> a1 = {-1, 0, 1};
    std::vector<int> b1 = {-1, 0, 1};
    s21::vector<int> a3 = {-2, 3, 4};
    std::vector<int> b3 = {-1, 0, 1};
    // b3.swap(a3);
    a1.pop_back();
    b1.pop_back();
    EXPECT_EQ(a1.back(), b1.back());
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    a1.pop_back();
    b1.pop_back();
    EXPECT_EQ(a1.back(), b1.back());
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    a1.pop_back();
    b1.pop_back();
    try {
        a1.pop_back();
    } catch (std::out_of_range &error){
        EXPECT_EQ(error.what(), std::string("s21::vector::pop_back: nothing to delete..."));
    }
}



TEST(vector_test, is_empty_and_size) {
    s21::vector<int> a1 = {-1, 0, 4, 8};
    s21::vector<int> b1;
    EXPECT_EQ(a1.empty(), false);
    EXPECT_EQ(b1.empty(), true);
    EXPECT_EQ(a1.size(), 4);
    EXPECT_EQ(b1.size(), 0);
}

TEST(vector_test, reserve) {
    s21::vector<int> a1 = {-1, 0, 4, 8};
    std::vector<int> b1 = {-1, 0, 4, 8};
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    s21::vector<int> a3(4);
    a3.reserve(2);
    a1.reserve(100);
    b1.reserve(100);
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());

    try {
        a1.reserve(-100);
    } catch (std::out_of_range &error){
        EXPECT_EQ(error.what(), std::string("s21::vector::reserve: Reserve capacity can't be larger than max_size!"));
    }
}

TEST(vector_test, shrink) {
    s21::vector<int> a1 = {0, 1, 2, 3, 4};
    std::vector<int> b1 = {0, 1, 2, 3, 4};
    a1.push_back(5);
    b1.push_back(5);
    a1.push_back(6);
    b1.push_back(6);
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    a1.shrink_to_fit();
    b1.shrink_to_fit();
    std::vector<int> b2 = {0, 1, 2, 3};
    b2.shrink_to_fit();

    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
}

TEST(vector_test, clear) {
    s21::vector<int> a1 = {-1, 0, 4, 8};
    std::vector<int> b1 = {-1, 0, 4, 8};
    s21::vector<int> a2;
    std::vector<int> b2;
    a1.clear();
    b1.clear();
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    a2.clear();
    b2.clear();
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
}


TEST(vector_test, erase) {
    s21::vector<int> a1 = {0, 1, 2, 3, 4};
    std::vector<int> b1 = {0, 1, 2, 3, 4};

    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    auto it1 = a1.end();
    auto it2 = b1.end();
    a1.erase(it1- 1);
    b1.erase(it2- 1);
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    try {
        a1.erase(it1 + 10);
    } catch (std::out_of_range &error){
        EXPECT_EQ(error.what(), std::string("s21::vector::insert Unable to insert into a position out of range of begin to end"));
    }
}

TEST(vector_test, insert) {
    s21::vector<int> a1 = {0, 1, 2, 3, 4};
    std::vector<int> b1 = {0, 1, 2, 3, 4};
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    auto it1 = a1.end();
    auto it2 = b1.end();
    int test1 = 15;

    a1.insert(it1- 2, test1);
    b1.insert(it2- 2, test1);
    EXPECT_EQ(a1.size(), b1.size());
    EXPECT_EQ(a1.capacity(), b1.capacity());
    EXPECT_EQ(a1[5], b1[5]);
    EXPECT_EQ(a1[3], b1[3]);
    try {
        a1.insert(it1 + 10, 11);
    } catch (std::out_of_range &error){
        EXPECT_EQ(error.what(), std::string("s21::vector::insert Unable to insert into a position out of range of begin to end"));
    }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}