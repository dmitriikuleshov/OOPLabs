#include "../include/array.hpp" // Заголовочный файл с вашим классом Array
#include <gtest/gtest.h>

// Тестирование конструктора по умолчанию
TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_GE(arr.capacity(), 2); // Так как вместимость начинается с 2
}

// Тестирование конструктора копирования
TEST(ArrayTest, CopyConstructor) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);

    Array<int> arr_copy = arr;

    EXPECT_EQ(arr_copy.size(), 2);
    EXPECT_EQ(arr_copy[0], 10);
    EXPECT_EQ(arr_copy[1], 20);
}

// Тестирование оператора присваивания копированием
TEST(ArrayTest, CopyAssignmentOperator) {
    Array<int> arr;
    arr.push_back(5);
    arr.push_back(15);

    Array<int> arr_copy;
    arr_copy = arr;

    EXPECT_EQ(arr_copy.size(), 2);
    EXPECT_EQ(arr_copy[0], 5);
    EXPECT_EQ(arr_copy[1], 15);
}

// Тестирование конструктора перемещения
TEST(ArrayTest, MoveConstructor) {
    Array<int> arr;
    arr.push_back(7);
    arr.push_back(14);

    Array<int> arr_moved = std::move(arr);

    EXPECT_EQ(arr_moved.size(), 2);
    EXPECT_EQ(arr_moved[0], 7);
    EXPECT_EQ(arr_moved[1], 14);
    EXPECT_EQ(arr.size(), 0); // arr должен быть пустым после перемещения
}

// Тестирование оператора присваивания перемещением
TEST(ArrayTest, MoveAssignmentOperator) {
    Array<int> arr;
    arr.push_back(3);
    arr.push_back(9);

    Array<int> arr_moved;
    arr_moved = std::move(arr);

    EXPECT_EQ(arr_moved.size(), 2);
    EXPECT_EQ(arr_moved[0], 3);
    EXPECT_EQ(arr_moved[1], 9);
    EXPECT_EQ(arr.size(), 0); // arr должен быть пустым после перемещения
}

// Тестирование метода push_back (копирование)
TEST(ArrayTest, PushBackCopy) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

// ТУТ ВАЛИТСЯ
// Тестирование метода push_back (перемещение)
TEST(ArrayTest, PushBackMove) {
    Array<std::string> arr;
    std::string str = "Hello";
    arr.push_back(std::move(str));
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], "Hello");
    EXPECT_EQ(str, ""); // Строка str должна быть пустой после перемещения
}

// // Тестирование метода emplace_back
TEST(ArrayTest, EmplaceBack) {
    Array<std::pair<int, std::string>> arr;
    arr.emplace_back(1, "One");
    arr.emplace_back(2, "Two");

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0].first, 1);
    EXPECT_EQ(arr[0].second, "One");
    EXPECT_EQ(arr[1].first, 2);
    EXPECT_EQ(arr[1].second, "Two");
}

// // Тестирование метода pop_back
TEST(ArrayTest, PopBack) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    arr.pop_back();

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// // Тестирование метода clear
TEST(ArrayTest, Clear) {
    Array<int> arr;
    arr.push_back(5);
    arr.push_back(15);
    arr.push_back(25);

    arr.clear();

    EXPECT_EQ(arr.size(), 0);
}

// // Тестирование доступа к элементам через оператор []
TEST(ArrayTest, AccessOperator) {
    Array<int> arr;
    arr.push_back(100);
    arr.push_back(200);

    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
}

// // Тестирование исключения при выходе за пределы массива
TEST(ArrayTest, OutOfBoundsAccess) {
    Array<int> arr;
    arr.push_back(50);

    EXPECT_THROW(arr[1], std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}