#include <iostream>

#include <vector>
#include <forward_list>

#include <utility>
#include <initializer_list>
#include <algorithm>

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

// default constructor
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table() = default;

// parametrized constructor
// constructs a hash_table with 'count' default elements 
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table(size_t count)
    : _buffer{count}, _size{count}
{
    std::pair<Key, Value> pair;
    for(size_t i{}; i < count; ++i)
    {
        _buffer[hash(key)].push_front(pair);
    }
}

// parametrized constructor
// constructs a hash_table with 'count' elements
// and initializes them with the given pair
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table
    (size_t count, std::pair<Key, Value> val)
        : _buffer{count}, _size{count}
{
    for(size_t i{}; i < count; ++i)
    {
        _buffer[hash(val.first)].push_front(val);
    }
}

// parametrized constructor
// constructs a hash_table with 'count' elements
// and initializes them with the given key and value
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table
    (size_t count, Key key, Value value)
        : _buffer{count}, _size{count}
{
    std::pair<Key, Value> pair{key, value};
    for(size_t i{}; i < count; ++i)
    {
        _buffer[hash(key)].push_front(pair);
    }
}

// constructor with initializer list
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table
    (std::initializer_list<std::pair<Key, Value>>& init)
        : _buffer{init.size()}, _size{init._size()}
{
    auto end = init.end();
    for(auto it = init.begin(); it != end; ++i)
    {
        _buffer[hash((*it).first)] = *it;
    }
}

// copy constructor
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table
    (const hash_table<Key, Value>& oth)
        : _buffer{oth._buffer}, _size{oth._size}
{
}

// move constructor
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table
    (hash_table<Key, Value>&& oth)
        : _buffer{std::move(oth._buffer)}, _size{oth._size}
{
}

// destructor /default/
template <typename Key, typename Value>
hash_table<Key, Value>::~hash_table() = default;


// OPERATORS

// copy assignment operator
template <typename Key, typename Value>
hash_table<Key, Value>& hash_table<Key, Value>::operator=
    (const hash_table<Key, Value>& rhs)
{
    _buffer = oth._buffer;
    _size = oth._size;
}

// move assignment operator
template <typename Key, typename Value>
hash_table<Key, Value>& hash_table<Key, Value>::operator=
    (hash_table<Key, Value>&& rhs)
{
    _buffer = std::move(rhs._buffer);
    _size = oth._size;
}

// global operator<< for std::ostream objects
template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const hash_table<Key, Value>& obj)
{
    for(size_t i{}; i < obj._size; ++i)
    {
        auto end = obj._buffer[i].end();
        for(auto it = obj._buffer[i].begin(); it != enf; ++i)
        {
            os << (*it).first << "   " << (*it).second << "\n";
        }
    }
    return os;
}

// operator[]
// returns a reference to the element with the given key
// if there is not en element with the given key
// creates it with a default value
template <typename Key, typename Value>
Value& hash_table<Key, Value>::operator[](const Key& key)
{
    int hash_result = hash(key);
    auto begin = _buffer[hash_result].begin();
    auto end = _buffer[hash_result].end();
    for(; begin != end; ++begin)
    {
        if(*begin == key)
            return (*begin).second;
    }
    std::pair<Key, Value> pair;
    pair.first = key;
    _buffer[hash_result].push_front(pair);
    return _buffer[hash_result].front().second;
}

// operator[] (const)
// returns a const reference to the element with the
// given key as an rvalue
// if there is not an element with the given key
// creates it with a default value;
template <typename Key, typename Value>
const Value& hash_table<Key, Value>::operator[](const Key& key) const
{
    return const_cast<const Value&>(this->operator[key]);
}


