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

template <typename Value>
size_t hash_table<int, Value>::hash(int key)
{
    return key % _size;
}


