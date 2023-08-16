#include <gtest/gtest.h>
#include "../s21_containersplus.h"
#include <array>


TEST(array_test, constructor_1) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    EXPECT_EQ(array1.max_size(), array2.max_size());
    EXPECT_EQ(array1.size(), array2.size());
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(array1.at(i), array2.at(i));
    }

    s21::array<char, 5> arr3;
    std::array<char, 5> arr4;
    EXPECT_EQ(arr3.size(), arr4.size());
    EXPECT_EQ(arr3.max_size(), arr4.max_size());
}




TEST(array_test, constructor_3) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    const std::array<char, 5> array3 = {'1', '2', '3', '4', '5'};
    array3.at(3);
    EXPECT_EQ(array3[2], '3');
    auto a = std::move(array1);
    auto b = std::move(array2);
    EXPECT_EQ(array1.size(), array2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
    }
    
}

TEST(array_test, constructor_4) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    auto a = array1;
    auto b = array2;
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(array1.size(), array2.size());

    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
    } 
}

TEST(array_test, constructor_5) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    s21::array<char, 5> a;
    std::array<char, 5> b;
    a = std::move(array1);
    b = std::move(array2);
    EXPECT_EQ(array1.size(), array2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(array_test, at) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(array1.at(i), array2.at(i));
    }
    EXPECT_ANY_THROW(array1.at(-2));
}

TEST(array_test, operator) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    const std::array<char, 5> array_end = {'1', '2', '3', '4', '5'};
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(array1[i], array2[i]);
    }
    const s21::array<char, 5> array5 = {'1', '2', '3', '4', '5'};
    const s21::array<char, 5> arrayback = {'1', '2', '3', '4', '5'};
    auto i1=  array5.begin();
    auto i2=  array_end.end();
    EXPECT_EQ(*i1, *i2);

    EXPECT_EQ(array5.front(), '1');
    EXPECT_EQ(*(array5.data()), '1');
    EXPECT_EQ(arrayback.back(), '5');
    EXPECT_EQ(array1.front(), array2.front());
    EXPECT_EQ(array1.back(), array2.back());
    s21::array<char, 5> array3;
    EXPECT_EQ(array1.front(), array2.front());
    EXPECT_EQ(array1.back(), array2.back());

}



TEST(array_test, data) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    EXPECT_EQ(*(array1.data()), *(array2.data()));
    s21::array<char, 5> array3;
    EXPECT_EQ(*(array3.data()), 0);
}


TEST(array_test, begin_end) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    auto it1 = array1.begin();
    auto it2 = array2.begin();
    auto it3 = array1.end();
    auto it4 = array2.end();
    it3--; it3--;
    it4--; it4--;
    EXPECT_EQ(*it3, *it4);
    EXPECT_EQ(*it1, *it2);
}


TEST(array_test, empty) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    EXPECT_EQ(array1.empty(), array2.empty());
    s21::array<char, 5> array3;
    std::array<char, 5> array4;
    EXPECT_EQ(array3.empty(), array4.empty());
}


TEST(array_test, size) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    s21::array<char, 5> array3;
    std::array<char, 5> array4;
    EXPECT_EQ(array1.size(), array2.size());
    EXPECT_EQ(array1.max_size(), array2.max_size());
    EXPECT_EQ(array3.size(), array4.size());
    s21::array<int, 5> array5;
    std::array<int, 5> array6;
    EXPECT_EQ(array5.max_size(), array6.max_size());

}


TEST(array_test, swap) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    s21::array<char, 5> a;
    std::array<char, 5> b;
    array1.swap(a);
    array2.swap(b);
    EXPECT_EQ(array1.size(), array2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
    }
    s21::array<char, 5> array3 = {'6', '7', '8', '9', '0'};
    std::array<char, 5> array4 = {'6', '7', '8', '9', '0'};
    array3.swap(a);
    array4.swap(b);
    EXPECT_EQ(array3.size(), array4.size());
    EXPECT_EQ(a.size(), b.size());

}


TEST(array_test, fill) {
    s21::array<char, 1> array1;
    std::array<char, 1> array2;
    array1.fill(100);
    array2.fill(100);
    EXPECT_EQ(array1.size(), array2.size());
    auto it1 = array1.begin();
    for (auto it2 = array2.begin(); it2 != array2.end(); ++it2) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(array_test, iterator_1) {
    s21::array<char, 5> array1 = {'1', '2', '3', '4', '5'};
    std::array<char, 5> array2 = {'1', '2', '3', '4', '5'};
    auto it1 = array1.begin();
    auto it2 = array2.begin();
    for (int i = 0; i < 4; i++) {
        ++it1, ++it2;
    }
    EXPECT_EQ(*it1, *it2);
    auto it3 = array1.end();
    auto it4 = array2.end();
    it3--;
    it4--;
    EXPECT_EQ(*it3, *it4);
    it4 = array1.end();
    it3++;
    EXPECT_EQ(it3 == it4, true);


}

TEST(array_test, constructor_throw) {
    try {
        s21::array<int, 5> a = {1, 2, 3, 4, 5, 6};
    } catch(std::runtime_error &error) {
        EXPECT_EQ(error.what(), std::string("s21::array: Initializer_list's size is not the same as the array's size!"));
    }
}

TEST(array_test, at_const) {
    const s21::array<int, 6> a = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(a.at(3), 4);
    ASSERT_ANY_THROW(a.at(8));
}

TEST(array_test, operator_square_brackets) {
    const s21::array<int, 6> a = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(a[3], 4);
}

TEST(array_test, end_const) {
    const s21::array<int, 6> a = {1, 2, 3, 4, 5, 6};
    for (auto el : a) {
        EXPECT_EQ(el, el);
    }
}
