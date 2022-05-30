#include <iostream>
#include <vector>
#include <list>

#include <utility>
#include <initializer_list>

#include "hash_table.hpp"

template <typename Key, typename Value>
size_t hash_table<Key, Value>::hash(const Key& key)
{
    return int(key) % _size;
}