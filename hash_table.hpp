#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <fstream>

#include <vector>
#include <list>

#include <utility>
#include <initializer_list>

template <typename Key, typename Value>
class hash_table
{
public: // THE C-TORS AND THE D-TOR

    // default c-tor
    hash_table() = default;

    // parametrized ctor
    // constructs a hash_table with a certain count
    // default initializes the member
    hash_table(size_t);

    // parametrized c-tor
    // constructs a hash_table with a certain count
    // initializes the elements by the given vakue
    hash_table(size_t, std::pair<Key, Value>);

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
    friend std::ostream& operator<<(std::ostream&, hash_table<Key, Value>);

    // global out-stream operator for std::ofstream objects
    friend std::ofstream& operator<<(std::ofstream&, hash_table<Key, Value>);

    // subscript operator 
    // returns the bucket within a specific position
    // the bucket can be change later
    // in this hash_table a bucket is an std::list
    std::list<std::pair<Key, Value>>& operator[](size_t);

    // subscript operator (const)
    // returns the bucket within a specific position
    // the bucket cannot be changed later
    // in this hash)table a buvket is an std::list
    const std::list<std::pair<Key, Value>>& operator[](size_t) const;

    // operator is equal to
    bool operator==(const hash_table<Key, Value>&) const;

    // operator is not equal to
    bool operator!=(const hash_table<Key, Value>&) const;

    // operator +
    hash_table<Key, Value>& operator+(const hash_table<Key, Value>&);

    // operator +=
    const hash_table<Key, Value>& operator+=(const hash_table<key, Value>&) const;

    // operator is less than
    bool operator<(const hash_table<Key, Value>&) const;

    // operator is greather than
    bool operator>(const hash_table<Key, Value>&) const;

    // operator is less than or equal to
    bool operator<=(const hash_table<Key, Value>&) const;

    // operator is greather than or equal to
    bool operator>=(const hash_table<key, Value>&) const;

public: // MEMBER FUNCTIONS

    // checks whether the container is empty
    bool empty() const;

    // returns the size of the underlying array
    size_t size() const;

    // clears the contents of the container
    void clear();

    // inserts an element
    void insert(const std::pair<Key, Value>&);

    // constructs an element in-place
    template <typename Arg, typename... Args>
    void emplace(Arg, Args...);

    // erases the element with the given key
    // if there is not such element, does nothing
    void erase(const Key&);

    // swaps the contents of the container
    // with the hash_table container given as a parameter
    void swap(hash_table<Key, pair>&);

    // extracts nodes from the container
    // and returns that element
    // if ther is not such element, does nothing
    std::pair<Key, Value>& extract(const Key&);

    // splices nodes rfom the container given as a parameter
    void merge(hash_table<Key, Value>&);

    // returns the number of elements with the specific key
    size_t count(const Key&);

    // finds the element with the specific key
    const std::pair<Key, Value>& find(const Key&) const;

    // checks whether the container contains
    // an element with the given key
    bool contains(const Key&);

    // return the average number of elements per bucket
    // in this hash_table a bucket is an std::list
    size_t load_factor() const;

    // reserves at least the specified number of buckets
    // and regenerates the hash_table
    void rehash(size_t count);

    // this function is used to hash the keys
    size_t hash(const Key&);

private:

    // underlying array is an std::vector
    // each bucket is an std::list
    // each list contains <Key, Value> pairs
    std::vector<std::list<std::pair<Key, Val>>> _buffer;
    size_t _size;
};


// spectialization for std::string as a key
template <typename Value>
class hash_table<std::string, Value>
{
public:
    size_t hash(const std::string&);
};

// specialization for int as a key
template <typename Value>
class hash_table<int, Value>
{
public:
    size_t hash(int);
};

// specialization for long as a key
template <typename Value>
class hash_table<long, Value>
{
public:
    size_t hash(long);
};

// specialization for short as a key
template <typename Value>
class hash_table<short, Value>
{
public:
    size_t hash(short);
};

// specialization for char as a key
template <typename Value>
class hash_table<char, Value>
{
public:
    size_t hash(char);
};

// specialization for wchar_t as a key
template <typename Value>
class hash_table<wchar_t, Value>
{
public:
    size_t hash(wchar_t);
};

// specialization for float as a key
template <typename Value>
class hash_table<float, Value>
{
public:
    size_t hash(float);
};

// specialization for double as a key
template <typename Value>
class hash_table<double, Value>
{
public:
    size_t hash(double);
};

// specialization for long double as a key
template <typename Value>
class hash_table<long double, Value>
{
public:
    size_t hash(long double);
};

#endif // HASH_TABLE_H
