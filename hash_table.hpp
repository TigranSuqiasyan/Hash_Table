#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

#include <vector>
#include <forward_list>

#include <utility>
#include <initializer_list>
#include <algorithm>

template <typename Key, typename Value>
class hash_table
{
public: // THE C-TORS AND THE D-TOR

    // default c-tor
    hash_table();

    // parametrized c-tor
    // constructs a hash_table with a certain count
    // default initializes the member
    hash_table(size_t);

    // copy c-tor
    hash_table(const hash_table<Key, Value>&);

    // c-tor with initializer list
    hash_table(std::initializer_list<std::pair<Key, Value>>&);

    // move c-tor
    hash_table(hash_table<Key, Value>&&);

    // d-tor
    ~hash_table();

public: // OPERATORS

    // copy assignment operator
    hash_table& operator=(const hash_table<Key, Value>&);

    // move assignment operator
    hash_table& operator=(hash_table<Key, Value>&&);

    // global out-stream operator for std::ostream objects
    //friend std::ostream& operator<<(std::ostream&, const hash_table<Key, Value>&);

    // operator[]
    // returns a reference to the element stored in the hash_table
    // with the given key
    Value& operator[](const Key&);

    // operator[] (const)
    // returns a const reference to the element stored 
    // in the hash_table with the given key
    // (can't modify it)
    const Value& operator[](const Key&) const;

    // operator is equal to
    bool operator==(const hash_table<Key, Value>&) const;

    // operator is not equal to
    bool operator!=(const hash_table<Key, Value>&) const;

    // operator +
    hash_table<Key, Value> operator+(const hash_table<Key, Value>&) const;

    // operator +=
    const hash_table<Key, Value>& operator+=(const hash_table<Key, Value>&);

    // operator is less than
    bool operator<(const hash_table<Key, Value>&) const;

    // operator is greather than
    bool operator>(const hash_table<Key, Value>&) const;

    // operator is less than or equal to
    bool operator<=(const hash_table<Key, Value>&) const;

    // operator is greather than or equal to
    bool operator>=(const hash_table<Key, Value>&) const;

public: // MEMBER FUNCTIONS

    // checks whether the container is empty
    bool empty() const;

    // returns the number of elements stored
    size_t size() const;

    // clears the contents of the container
    void clear();

    // inserts an element
    void insert(const std::pair<Key, Value>&);

    // constructs an element in-place
    template <typename... Args>
    void emplace(Args...);

    // erases the element with the given key
    // if there is not such element, does nothing
    void erase(const Key&);

    // swaps the contents of the container
    // with the hash_table container given as a parameter
    void swap(hash_table<Key, Value>&);

    // extracts nodes from the container
    // and returns that element
    // if there is not such element, does nothing
    std::pair<Key, Value>& extract(const Key&);

    // splices nodes from the container given as a parameter
    void merge(hash_table<Key, Value>&);

    // returns the number of elements with the specific key
    size_t count(const Key&);

    // finds the element with the specific key
    const std::pair<Key, Value>& find(const Key&) const;

    // checks whether the container contains
    // an element with the given key
    bool contains(const Key&) const;

    // returns the average number of elements per bucket
    // in this hash_table a bucket is an std::list
    size_t load_factor() const;

    // reserves at least the specified number of buckets
    // and regenerates the hash_table
    void rehash(size_t count);

    // this function is used to hash the keys
    size_t hash(const Key&);

protected:

    // underlying array is an std::vector
    // each bucket is an std::list
    // each list contains <Key, Value> pairs
    std::vector<std::forward_list<std::pair<Key, Value>>> _buffer;
    size_t _array_size;
    size_t _elements_count;
};

#endif // HASH_TABLE_H