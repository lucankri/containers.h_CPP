#include <gtest/gtest.h>
#include "../s21_containers.h"
#include <set>

struct structure {
        int x_;
        long double y_;
        char z_;
        bool operator==(const structure &other) const {
            return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
        }
        bool operator>(const structure &other) const { return x_ > other.x_; }
        bool operator<(const structure &other) const { return x_ < other.x_; }
        bool operator>=(const structure &other) const { return x_ >= other.x_; }
        bool operator<=(const structure &other) const { return x_ <= other.x_; }
        structure() {
            x_ = 0;
            y_ = 0;
            z_ = 0;
        }
        structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
    };

TEST(set_test, constructor_1) {
    s21::set<int> set1;
    std::set<int> set2;
    s21::set<int> set3 = {1, 2, 3};
    s21::set<int> set4 = set3;
    s21::set<int> set5 = std::move(set4);
    const s21::set<int> set_const = {1, 2, 3};
    const s21::set<int> set_const2 = {1, 2, 3};
    auto it1 = set_const.begin();
    for (auto it2 = set_const2.begin(); it2 != set_const2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    const std::set<int> set_const3 = {1, 2, 3};
    auto it2 = set_const.end();
    it2--;
    auto it3 = set_const3.end();
    it3--;
    EXPECT_EQ(*it2, *it3);
    EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, test2) {
    s21::set<char> set1 = {'a', '2', 'c'};
    std::set<char> set2 = {'a', '2', 'c'};
    set1.max_size();
    set2.max_size();

    EXPECT_EQ(*(set2.find('a')),*(set1.find('a')));
    const s21::set<char> set3 = {'a', '2', 'c'};
    const std::set<char> set4 = {'a', '2', 'c'};
    EXPECT_EQ(*(set3.find('a')),*(set4.find('a')));
}

TEST(set_test, constructor_2) {
    s21::set<char> set1 = {'a', '2', 'c'};
    std::set<char> set2 = {'a', '2', 'c'};
    auto it1 = set1.begin();
    for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(set_test, constructor_3) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    auto a = std::move(set1);
    auto b = std::move(set2);
    auto it1 = a.begin();
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(a.size(), b.size());
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(set_test, constructor_4) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    auto a = set1;
    auto b = set2;
    auto it1 = a.begin();
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(a.size(), b.size());
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }

}

TEST(set_test, end_1) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    auto it1 = set1.end();
    auto it2 = set2.end();
    it1--, it2--;
    EXPECT_EQ(*it2, *it1);
}


TEST(set_test, begin_1) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    auto it1 = set1.begin();
    auto it2 = set2.begin();
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, begin_2) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    set1.clear();
    set2.clear();
    auto it1 = set1.begin();
    auto it2 = set2.begin();
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, size_1) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, size_2) {
    s21::set<char> set1;
    std::set<char> set2;
    set1.insert('d');
    set2.insert('d');
    EXPECT_EQ(set1.size(), set2.size());
}


TEST(set_test, empty_clear) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    EXPECT_EQ(set1.empty(), set2.empty());
    EXPECT_EQ(set1.size(), set2.size());
    set1.clear();
    set2.clear();
    EXPECT_EQ(set1.empty(), set2.empty());
    EXPECT_EQ(set1.size(), set2.size());
    s21::set<char> empty1;
    std::set<char> empty2;
    empty1.clear();
    empty2.clear();
    EXPECT_EQ(empty1.size(), empty2.size());
    EXPECT_EQ(empty1.empty(), empty2.empty());
}



TEST(set_test, insert_1) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(set1.insert('e').second, set2.insert('e').second);
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(*(set1.insert('e').first), *(set2.insert('e').first));
    EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, insert2) {
    s21::set<char> set1;
    std::set<char> set2;
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(set1.insert('e').second, set2.insert('e').second);
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(*(set1.insert('e').first), *(set2.insert('e').first));
    EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, erase_1) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    auto it1= set1.begin();
    auto it2= set2.begin();
    set1.erase(it1);
    set2.erase(it2);
    EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, erase_2) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    EXPECT_EQ(set1.size(), set2.size());
    auto it1= set1.begin();
    auto it2= set2.begin();
    set1.erase(it1);
    set2.erase(it2);
    EXPECT_EQ(set1.size(), set2.size());
}



TEST(set_test, swap) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};
    s21::set<char> a;
    std::set<char> b;
    set1.swap(a);
    set2.swap(b);
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    set1 = {'a', '2', 'c', '4'};
    set2 = {'a', '2', 'c', '4'};
    set1.swap(a);
    set2.swap(b);
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(a.size(), b.size());
    it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(set_test, merge_1) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};    
    s21::set<char> a = {'e', '6', 'g', '8'};
    std::set<char> b = {'e', '6', 'g', '8'};
    set1.merge(a);
    set2.merge(b);
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it1 = set1.begin();
    for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(set_test, merge_2) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};      
    s21::set<char> a = {'a', '2', 'c', '4'};
    std::set<char> b = {'a', '2', 'c', '4'};  
    set1.merge(a);
    set2.merge(b);
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it1 = set1.begin();
    for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(set_test, merge_3) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    std::set<char> set2 = {'a', '2', 'c', '4'};      
    s21::set<char> a = {'a', '2', 'c', '4', 'a', '2'};
    std::set<char> b = {'a', '2', 'c', '4', 'a', '2'};  
    set1.merge(a);
    set2.merge(b);
    EXPECT_EQ(set1.size(), set2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it1 = set1.begin();
    for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(set_test, iterator_1) {
    s21::set<char> set1 = {'a', '2', 'c', '4', 'e', '6'};
    s21::set<char> set2 = {'a', '2', 'c', '4', 'e', '6'};
    auto it1 = set1.begin();
    auto it2 = set2.begin();
    for (int i = 0; i < 6; i++) {
        it1++, it2++;
    }
    it1 = set1.end();
    it2 = set2.end();
    for (int i = 0; i < 6; i++) {
        it1--, it2--;
    }
    EXPECT_EQ(*it1, *it2);
}


TEST(set_test, iterator_2) {
    s21::set<char> set1 = {'a', '2', 'c', '4', 'e', '6'};
    s21::set<char> set2 = {'a', '2', 'c', '4', 'e', '6'};
    auto it1 = set1.begin();
    auto it2 = set2.begin();
    it1++;
    EXPECT_EQ(it1 != it2, true);
    auto it3 = set1.end();
    auto it4 = set2.end();
    for (int i = 0; i < 3; i++) {
        it3--, it4--;
    }
    EXPECT_EQ(it3 == it4, false);
    EXPECT_EQ(*it3, *it4);
}


TEST(set_test, contains_1) {
    s21::set<char> set1 = {'a', '2', 'c', '4'};
    s21::set<char> set2 = {'a', '2', 'c', '4'};    
    EXPECT_EQ(set1.contains('d'), false);
    EXPECT_EQ(set2.contains('a'), true);
}

