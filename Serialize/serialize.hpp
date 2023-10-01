#pragma once
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <map>


template <typename T>
concept Serializable = requires(const T & obj, std::ostream & os, std::istream & is) {
    { serialize(obj, os) } -> std::same_as<void>;
    { deserialize(obj, is) } -> std::same_as<void>;
};


template <typename T>
struct serializer {
    static void apply(const T& obj, std::ostream& os) {
        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&obj);
        std::ostream_iterator<uint8_t> oi(os);
        std::copy(ptr, ptr + sizeof(T), oi);
    }
};


template <typename T>
struct deserializer {
    static void apply(T& val, std::istream& is) {
        uint8_t* ptr = reinterpret_cast<uint8_t*>(&val);
        std::istream_iterator<uint8_t> ii(is);
        std::copy_n(ii, sizeof(T), ptr);
    }
};



template <typename T>
//typename std::enable_if<
//    std::is_same<decltype(serialize(std::declval<T>(), std::declval<std::ostream>())), void>::value
//>::type
void serialize(const T& obj, std::ostream& os)
{
    serializer<T>::apply(obj, os);
}

template <typename T>
//typename std::enable_if<
//    std::is_same<decltype(serialize(std::declval<T>(), std::declval<std::ostream>())), void>::value
//>::type
void deserialize(T& obj, std::istream& is)
{
    return deserializer<T>::apply(obj, is);
}


// ������������� ��� std::string
template <>
struct serializer<std::string> {
    static void apply(const std::string& str, std::ostream& os) {
        // ������� ����������� ������ ������
        serialize(static_cast<uint32_t>(str.size()), os);
        // ����� ����������� ������� ������
        for (char c : str) {
            serialize(c, os);
        }
    }
};

template <>
struct deserializer<std::string> {
    static void apply(std::string& str, std::istream& is) {
        // ������������� ������ ������
        uint32_t size;
        deserialize(size, is);
        str.resize(size);
        // ������������� ������� ������
        for (char& c : str) {
            deserialize(c, is);
        }
    }
};


// ������������� ��� std::vector
template <typename T>
struct serializer<std::vector<T>> {
    static void apply(const std::vector<T>& vec, std::ostream& os) {
        // ������� ����������� ������ �������
        serialize(static_cast<uint32_t>(vec.size()), os);
        // ����� ����������� �������� �������
        for (const T& item : vec) {
            serialize(item, os);
        }
    }
};

template <typename T>
struct deserializer<std::vector<T>> {
    static void apply(std::vector<T>& vec, std::istream& is) {
        // ������������� ������ �������
        uint32_t size;
        deserialize(size, is);
        vec.resize(size);
        // ������������� �������� �������
        for (T& item : vec) {
            deserialize(item, is);
        }
    }
};


// ������������� ��� std::map
template <typename K, typename V>
struct serializer<std::map<K, V>> {
    static void apply(const std::map<K, V>& map, std::ostream& os) {
        // ������� ����������� ������ map
        serialize(static_cast<uint32_t>(map.size()), os);
        // ����� ����������� ����� � ��������
        for (const auto& pair : map) {
            serialize(pair.first, os);
            serialize(pair.second, os);
        }
    }
};

template <typename K, typename V>
struct deserializer<std::map<K, V>> {
    static void apply(std::map<K, V>& map, std::istream& is) {
        // ������������� ������ map
        uint32_t size;
        deserialize(size, is);
        map.clear();
        // ������������� ����� � ��������
        for (uint32_t i = 0; i < size; ++i) {
            K key;
            V value;
            deserialize(key, is);
            deserialize(value, is);
            map[key] = value;
        }
    }
};
