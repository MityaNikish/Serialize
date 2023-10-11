#include "pch.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "serialize.hpp"
#include <unordered_map>


//int main()
//{
//    std::ofstream ofs("test.ser", std::ofstream::out | std::ofstream::binary);
//
//    char hello[7] = "hello!";
//    int boo[3] = { 1, 2, 3 };
//
//    serialize(hello, ofs);
//    serialize(boo, ofs);
//
//    char hello2[7];
//    int boo2[3];
//
//    ofs.close();
//
//    std::ifstream ifs("test.ser", std::ifstream::in | std::ifstream::binary);
//    ifs >> std::noskipws;
//
//    deserialize(hello2, ifs);
//    deserialize(boo2, ifs);
//
//    if (std::equal(hello, hello + 7, hello2))
//        std::cout << "Hello OK!" << std::endl;
//
//    if (std::equal(boo, boo + 3, boo2))
//        std::cout << "Boo OK!" << std::endl;
//
//    RUN_ALL_TESTS();
//    return 0;
//}


TEST(Vector, Int) {
    const std::vector<int> writable_vector = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> readable_vector;
    std::stringstream ss;

    ASSERT_NO_THROW({ serialize(writable_vector, ss); });

    ss >> std::noskipws;
    
    ASSERT_NO_THROW({ readable_vector = deserialize<std::vector<int>>(ss); });

    EXPECT_EQ(writable_vector, readable_vector);
}

TEST(Vector, Double) {
    const std::vector<double> writable_vector = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };
    std::vector<double> readable_vector;
    std::stringstream ss;

    ASSERT_NO_THROW({ serialize(writable_vector, ss); });

    ss >> std::noskipws;
    ASSERT_NO_THROW({ readable_vector = deserialize<std::vector<double>>(ss); });

    EXPECT_EQ(writable_vector, readable_vector);
}


TEST(Vector, Char) {
    const std::vector<char> writable_vector = { 'a', 'b', 'c', 'd' };
    std::vector<char> readable_vector;
    std::stringstream ss;

    ASSERT_NO_THROW({ serialize(writable_vector, ss); });

    ss >> std::noskipws;
    ASSERT_NO_THROW({ readable_vector = deserialize<std::vector<char>>(ss); });

    EXPECT_EQ(writable_vector, readable_vector);
}

TEST(Vector, String) {
    const std::vector<std::string> writable_vector = { "First", "Second", "Third", "and etc" };
    std::vector<std::string> readable_vector;
    std::stringstream ss;

    ASSERT_NO_THROW({ serialize(writable_vector, ss); });

    ss >> std::noskipws;
    ASSERT_NO_THROW({ readable_vector = deserialize<std::vector<std::string>>(ss); });

    EXPECT_EQ(writable_vector, readable_vector);
}

TEST(String, _) {
    const std::string writable_string("I hate template )<\nIt is joke (;");
    std::string readable_string;
    std::stringstream ss;

    ASSERT_NO_THROW({ serialize(writable_string, ss); });

    ss >> std::noskipws;
    ASSERT_NO_THROW({ readable_string = deserialize<std::string>(ss); });

    EXPECT_EQ(writable_string, readable_string);
}

TEST(Map, IntInt) {
    const std::map<int, int> writable_map = { {1, 456}, {2, 123}, {3, 798} };
    std::map<int, int> readable_map;
    std::stringstream ss;

    using type = std::map<int, int>;

    ASSERT_NO_THROW({ serialize(writable_map, ss); });

    ss >> std::noskipws;
    ASSERT_NO_THROW({ readable_map = deserialize<type>(ss); });

    EXPECT_EQ(writable_map, readable_map);
}


TEST(Map, StringInt) {
    const std::map<std::string, int> writable_map = { {"Count student", 5245}, {"Count teacher", 602}, {"Count deaths", 1} };
    std::map<std::string, int> readable_map;
    std::stringstream ss;

    using type = std::map<std::string, int>;

    ASSERT_NO_THROW({ serialize(writable_map, ss); });

    ss >> std::noskipws;
    ASSERT_NO_THROW({ readable_map = deserialize<type>(ss); });

    EXPECT_EQ(writable_map, readable_map);
}

TEST(Map, StringVector) {
    const std::map<std::string, std::vector<int>> writable_map = { {"False estimation student", {5, 4, 5, 5}}, {"True estimation student", {3, 3, 3, 2}} };
    std::map<std::string, std::vector<int>> readable_map;
    std::stringstream ss;

    using type = std::map<std::string, std::vector<int>>;

    ASSERT_NO_THROW({ serialize(writable_map, ss); });

    ss >> std::noskipws;
    ASSERT_NO_THROW({ readable_map = deserialize<type>(ss); });

    EXPECT_EQ(writable_map, readable_map);
}


class Container final
{
public:
    Container() = default;
    Container(int arg) : arg_(arg) {}
    //int getArg() { return arg_; }
    //void setArg(const int arg) { arg_ = arg; }
    //ContainerFirstType& operator=(const ContainerFirstType&) = default;
	bool operator==(const Container&) const = default;
private:
    int arg_;
};


TEST(MyClass, Int) {
    const Container writable_map(62169549);
    Container readable_map;
    std::stringstream ss;

    ASSERT_NO_THROW({ serialize(writable_map, ss); });

    ss >> std::noskipws;
    ASSERT_NO_THROW({ readable_map = deserialize<Container>(ss); });

    EXPECT_EQ(writable_map, readable_map);
}


//TEST(Heap, Int) {
//    const std::unordered_map<int, int> writable_map = { {1, 456}, {2, 123}, {3, 798} };
//    std::unordered_map<int, int> readable_map;
//    std::stringstream ss;
//
//    using type = std::unordered_map<int, int>;
//
//    ASSERT_NO_THROW({ serialize(writable_map, ss); });
//
//    ss >> std::noskipws;
//    ASSERT_NO_THROW({ readable_map = deserialize<type>(ss); });
//
//    EXPECT_EQ(writable_map, readable_map);
//}