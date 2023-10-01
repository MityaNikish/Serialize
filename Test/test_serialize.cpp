#include "pch.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "serialize.hpp"

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

    ASSERT_NO_THROW({ deserialize(readable_vector, ss); });

    EXPECT_EQ(writable_vector, readable_vector);
}

//TEST(Vector, Double) {
//    const std::vector<double> writable_vector = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };
//    std::vector<double> readable_vector;
//    std::stringstream ss;
//
//    ASSERT_NO_THROW({ serialize(writable_vector, ss); });
//
//    ASSERT_NO_THROW({ deserialize(readable_vector, ss); });
//
//    EXPECT_EQ(writable_vector, readable_vector);
//}


TEST(Vector, Char) {
    const std::vector<char> writable_vector = { 'a', 'b', 'c', 'd' };
    std::vector<char> readable_vector;
    std::stringstream ss;

    ASSERT_NO_THROW({ serialize(writable_vector, ss); });

    ASSERT_NO_THROW({ deserialize(readable_vector, ss); });

    EXPECT_EQ(writable_vector, readable_vector);
}

//TEST(String, _) {
//    const std::string writable_string("HellowWorld:)");
//    std::string readable_string;
//    std::stringstream ss;
//
//    std::ofstream ofs("test.ser", std::ofstream::out | std::ofstream::binary);
//    ASSERT_NO_THROW({ serialize(writable_string, ofs); });
//    ofs.close();
//
//    std::ifstream ifs("test.ser", std::ifstream::in | std::ifstream::binary);
//    ASSERT_NO_THROW({ deserialize(readable_string, ifs); });
//
//    EXPECT_EQ(writable_string, readable_string);
//}