#pragma once
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <map>


template <typename T>
struct is_std_container : std::false_type {};

template <typename... Args>
struct is_std_container<std::vector<Args...>> : std::true_type {};

template <typename Key, typename Value, typename... Args>
struct is_std_container<std::map<Key, Value, Args...>> : std::true_type {};

template <typename CharT, typename Traits, typename Allocator>
struct is_std_container<std::basic_string<CharT, Traits, Allocator>> : std::true_type {};


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
    static T apply(std::istream& is) {
        T val;
        uint8_t* ptr = reinterpret_cast<uint8_t*>(&val);
        std::istream_iterator<uint8_t> ii(is);
        std::copy_n(ii, sizeof(T), ptr);
        return val;
    }
};


template <typename T>
std::enable_if_t<is_std_container<T>::value || !std::is_class_v<T> || std::is_default_constructible_v<T> && std::is_trivially_copyable_v<T>, void>
serialize(const T& obj, std::ostream& os)
{
    serializer<T>::apply(obj, os);
}

template <typename T>
std::enable_if_t<is_std_container<T>::value || !std::is_class_v<T> || std::is_default_constructible_v<T> && std::is_trivially_copyable_v<T>, T>
deserialize(std::istream& is)
{
    return deserializer<T>::apply(is);
}


// специализация для std::string
template <>
struct serializer<std::string> {
    static void apply(const std::string& str, std::ostream& os) {
        serialize(static_cast<uint32_t>(str.size()), os);
        for (char c : str) {
            serialize(c, os);
        }
    }
};


template <>
struct deserializer<std::string> {
    static std::string apply(std::istream& is) {
        std::string str;
        str.resize(deserialize<uint32_t>(is));
        for (char& c : str) {
            c = deserialize<char>(is);
        }
        return str;
    }
};


// специализация для std::vector
template <typename T>
struct serializer<std::vector<T>> {
    static void apply(const std::vector<T>& vec, std::ostream& os) {
        serialize(static_cast<uint32_t>(vec.size()), os);
        for (const T& item : vec) {
            serialize(item, os);
        }
    }
};


template <typename T>
struct deserializer<std::vector<T>> {
    static std::vector<T> apply(std::istream& is) {
        std::vector<T> vec;
        vec.resize(deserialize<uint32_t>(is));
        for (T& item : vec) {
            item = deserialize<T>(is);
        }
        return vec;
    }
};


// специализация для std::map
template <typename K, typename V>
struct serializer<std::map<K, V>> {
    static void apply(const std::map<K, V>& map, std::ostream& os) {
        serialize(static_cast<uint32_t>(map.size()), os);
        for (const auto& pair : map) {
            serialize(pair.first, os);
            serialize(pair.second, os);
        }
    }
};


template <typename K, typename V>
struct deserializer<std::map<K, V>> {
    static std::map<K, V> apply(std::istream& is) {
        std::map<K, V> map;
        const uint32_t size = deserialize<uint32_t>(is);
        for (uint32_t i = 0; i < size; ++i) {
            K key;
            V value;
            key = deserialize<K>(is);
            value = deserialize<V>(is);
            map[key] = value;
        }
        return map;
    }
};
