#include <iostream>
#include <vector>
#include <list>

#include <utility>
#include <initializer_list>

#include "hash_table.hpp"

// implementation of the hash function
// using modulo arithmetic
// for type Key 'operator int' must be overloaded
template <typename Key, typename Value>
size_t hash_table<Key, Value>::hash(const Key& key)
{
    return int(key) % _size;
}

// implementation of the hash function
// specialization for std::string as a key
template <typename Value>
size_t hash_table<std::string, Value>::hash(const std::string& key)
{
    size_t result{};
    for(int i{}; i < key.size(); ++i) 
    {
        result += key[i];
    }
    return result % _size;
}

// implementation of the hash function
// specialization for int as a key
template <typename Value>
size_t hash_table<int, Value>::hash(int key)
{
    return key % _size;
}

// implemantation of the hash function
// specialization for long as a key
template <typename Value>
size_t hash_table<long, Value>::hash(long key)
{
    return key % _size;
}

// implementation of the hash fuction
// specialization for short as a key
template <typename Value>
size_t hash_table<short, Value>::hash(short key)
{
    return key % _size;
}

// implementation of the hash function
// specialization for char as a key
template <typename Value>
size_t hash_table<char, Value>::hash(char key)
{
    return key % _size;
}

// implementation of the hash function
// specialization for wchar_t as a key
template <typename Value>
size_t hash_table<wchar_t, Value>::hash(wchar_t key)
{
    return key % _size;
}

// implementetion of the hash function
// specialization for float as a key
template <typename Value>
size_t hash_table<float, Value>::hash(float key)
{
    size_t integral = static_cast<int>key;
    return integral % _size;
}

// implementation of the hash function
// specialization for double as a key
template <typename Value>
size_t hash_table<double, Value>::hash(double key)
{
    size_t integral = static_cast<int>key;
    return integral % _size;
}

// implementation for the hash function
// specialization for long double as a key
template <typename Value>
size_t hash_table<long double, Value>::hash(long double key)
{
    size_t integral = static_cast<int>key;
    return integral % _size;
}


