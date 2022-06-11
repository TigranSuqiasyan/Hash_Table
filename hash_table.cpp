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
    return int(key) % _array_size;
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
    return result % _array_size;
}

// implementation of the hash function
// specialization for int as a key
template <typename Value>
size_t hash_table<int, Value>::hash(int key)
{
    return key % _array_size;
}

// implemantation of the hash function
// specialization for long as a key
template <typename Value>
size_t hash_table<long, Value>::hash(long key)
{
    return key % _array_size;
}

// implementation of the hash fuction
// specialization for short as a key
template <typename Value>
size_t hash_table<short, Value>::hash(short key)
{
    return key % _array_size;
}

// implementation of the hash function
// specialization for char as a key
template <typename Value>
size_t hash_table<char, Value>::hash(char key)
{
    return key % _array_size;
}

// implementation of the hash function
// specialization for wchar_t as a key
template <typename Value>
size_t hash_table<wchar_t, Value>::hash(wchar_t key)
{
    return key % _array_size;
}

// implementetion of the hash function
// specialization for float as a key
template <typename Value>
size_t hash_table<float, Value>::hash(float key)
{
    size_t integral = static_cast<int>key;
    return integral % _array_size;
}

// implementation of the hash function
// specialization for double as a key
template <typename Value>
size_t hash_table<double, Value>::hash(double key)
{
    size_t integral = static_cast<int>key;
    return integral % _array_size;
}

// implementation for the hash function
// specialization for long double as a key
template <typename Value>
size_t hash_table<long double, Value>::hash(long double key)
{
    size_t integral = static_cast<int>key;
    return integral % _array_size;
}

// default constructor
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table() = default;

// parametrized constructor
// constructs a hash_table with 'count' default elements 
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table(size_t count)
    : _buffer{count}, 
    _array_size{count}, 
    _elements_count{}
{
}

// constructor with initializer list
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table
    (std::initializer_list<std::pair<Key, Value>>& init)
        : _buffer{init.size()}, 
        _array_size{init.size()}, 
        _elements_count{init.size()}
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
        : _buffer{oth._buffer}, 
        _array_size{oth._array_size}, 
        _elements_count{oth._elements_count}
{
}

// move constructor
template <typename Key, typename Value>
hash_table<Key, Value>::hash_table
    (hash_table<Key, Value>&& oth)
        : _buffer{std::move(oth._buffer)}, 
        _array_size{oth._array_size},
        _elements_count{oth._elements_count}
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
    _buffer = rhs._buffer;
    _array_size = rhs._array_size;
    _elements_count = rhs._elements_count;
}

// move assignment operator
template <typename Key, typename Value>
hash_table<Key, Value>& hash_table<Key, Value>::operator=
    (hash_table<Key, Value>&& rhs)
{
    _buffer = std::move(rhs._buffer);
    _array_size = rhs._array_size;
    _elements_count = rhs._elements_count;
}

/*// global operator<< for std::ostream objects
template <typename Key, typename Value>
std::ostream& operator<<
    (std::ostream& os, const hash_table<Key, Value>& obj)
{
    for(size_t i{}; i < obj._array_size; ++i)
    {
        auto end = obj._buffer[i].end();
        for(auto it = obj._buffer[i].begin(); it != enf; ++i)
        {
            os << (*it).first << "   " << (*it).second << "\n";
        }
    }
    return os;
}*/

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

// operator==
// checks whether the hash table passed as the parameters
// has the same elements as the object on which this
// function is called
template <typename Key, typename Value>
bool hash_table<Key, Value>::operator==
    (const hash_table<Key, Value>& rhs) const
{
    std::vector<std::pair<Key, Value>> first_contaier;
    std::vector<std::pair<Key, Value>> second_container;
    for(size_t i{}; i < _array_size; ++i)
    {
        auto begin = _buffer[i].begin();
        auto end = _buffer[i].end();
        for(; begin != end; ++begin)
        {
            first_contaier.push_back(*begin);
        }
    }

    for(size_t i{}; i < rhs._array_size; ++i)
    {
        auto begin = rhs._buffer[i].begin();
        auto end = rhs._buffer[i].end();
        for(; begin != end; ++begin)
        {
            second_container.push_back(*begin);
        }
    }
    return std::is_permutation(first_contaier.begin(),
        first_contaier.end(), second_container.begin());
}

// operator!=
// checks whether the hash_table passed as a parameter
// and our object on which the function is called
// differ from each other or not
template <typename Key, typename Value>
bool hash_table<Key, Value>::operator!=
    (const hash_table<Key, Value>& rhs) const
{
    return !((*this) == rhs);
}

// global operator+
// creates a hash_table which includes all the elements
// from both left-hand-side and right-hand-side elements
// returns the data structure by value
template <typename Key, typename Value>
hash_table<Key, Value> operator+
    (const hash_table<Key, Value>& lhs, 
    const hash_table<Key, Value>& rhs)
{
    size_t hash_result{};
    hash_table<key, Value> result{lhs._array_size + rhs._array_size};
    for(size_t i{}; i < lhs._array_size; ++i)
    {
        auto begin = lhs._buffer[i].begin();
        auto end = lhs._buffer[i].end();
        for(; begin != end; ++begin)
        {
            hash_result = result.hash((*begin).first);
            result._buffer[hash_result].push_front(*begin);
        }
    }
    for(size_t i{}; i < rhs._array_size; ++i)
    {
        auto begin = rhs._buffer[i].begin();
        auto end = rhs._buffer[i].end();
        for(; begin != end; ++begin)
        {
            hash_result = result.hash((*begin).first);
            result._buffer[hash_result].push_front(*begin);
        }
    }
    return result;
}

// operator+=
// concatinates the hash_table given as a parameter
// to the one on which that function is called
// returns a const reference to that object
template <typename Key, typename Value>
const hash_table<Key, Value>& hash_table<Key, Value>::operator+=
    (const hash_table<Key, Value>& rhs)
{
}

// this function checks whether our
// data structure is empty
template <typename Key, typename Value>
bool hash_table<Key, Value>::empty() const
{
    if(_buffer.empty())
        return true;
    bool result = true;
    for(size_t i{}; i < _array_size; ++i)
    {
        if(!_buffer[i].empty())
            return false;
    }
    return result;
}

// this function returns the number of elements
template <typename Key, typename Value>
size_t hash_table<Key, Value>::size() const
{
    return _elements_count;
}

// this function clears the contents
template <typename Key, typename Value>
void hash_table<Key, Value>::clear()
{
    _buffer.clear();
    _array_size = 0;
    _elements_count = 0;
}

// this function inserts an element
template <typename Key, typename Value>
void hash_table<Key, Value>::insert
    (const std::pair<Key, Value>& pair)
{
    if(_elements_count == _array_size)
    {
        this->rehash(_array_size * 2);
    }
    buffer[this->hash(pair.first)].push_front(pair);
}

// this function reserves at least the specified number
// of buckets and regenerates the hash_table
template <typename Key, typename Value>
void hash_table<Key, Value>::rehash(size_t count)
{
    std::vector<std::forward_list<std::pair<Key, Value>>> new_buffer(count);
    size_t hash_result{};
    for(size_t i{}; i < _array_size; ++i)
    {
        auto begin = _buffer[i].begin();
        auto end = _buffer[i].end();
        for(; begin != end; ++begin)
        {
            hash_result = this->hash((*begin).first);
            new_buffer[hash_result].push_front(*begin);
        }
    }
    _buffer = new_buffer;
    _array_size = count;
}

// constructs an element in-place
template <typename Key, typename Value, typename... Args>
void hash_table<Key, Value>::emplace
{

}

// erases the element with the given key
// if there is not such element, does nothing
template <typename Key, typename Value>
void hash_table<Key, Value>::erase(const Key& key)
{

}

// checks wheteher the container contains
// an element with the given key
template <typename Key, typename Value>
bool hash_table<Key, Value>::contains(const Key& key) const
{
    for(size_t i{}; i < _array_size; ++i)
    {
        auto begin = _buffer[i].begin();
        auto end = _buffer[i].end();
        for(; begin!= end; ++begin)
        {
            if((*begin).first == key)
                return true;
        }
    }
    return false;
}

// returns the average number of elements per bucket
template <typename Key, typename Value>
size_t hash_table<Key, Value>::load_factor() const
{
    return (static_cast<double>(_elements_count)) / _array_size;
}






