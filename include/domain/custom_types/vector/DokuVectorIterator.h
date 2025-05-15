//
// Created by belyashik2k on 5/15/25.
//

#ifndef DOKUVECTORITERATOR_H
#define DOKUVECTORITERATOR_H
#include <cstddef>
#include <iterator>

template<typename T>
class DokuVectorIterator {
    T* ptr;
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    explicit DokuVectorIterator(T* p = nullptr) : ptr(p) {}

    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }

    DokuVectorIterator& operator++() { ++ptr; return *this; }
    DokuVectorIterator operator++(int) { DokuVectorIterator tmp = *this; ++ptr; return tmp; }
    DokuVectorIterator& operator--() { --ptr; return *this; }
    DokuVectorIterator operator--(int) { DokuVectorIterator tmp = *this; --ptr; return tmp; }

    DokuVectorIterator operator+(difference_type n) const { return DokuVectorIterator(ptr + n); }
    DokuVectorIterator operator-(difference_type n) const { return DokuVectorIterator(ptr - n); }
    difference_type operator-(const DokuVectorIterator& other) const { return ptr - other.ptr; }

    DokuVectorIterator& operator+=(difference_type n) { ptr += n; return *this; }
    DokuVectorIterator& operator-=(difference_type n) { ptr -= n; return *this; }

    reference operator[](difference_type n) const { return *(ptr + n); }

    bool operator==(const DokuVectorIterator& other) const { return ptr == other.ptr; }
    bool operator!=(const DokuVectorIterator& other) const { return ptr != other.ptr; }
    bool operator<(const DokuVectorIterator& other) const { return ptr < other.ptr; }
    bool operator<=(const DokuVectorIterator& other) const { return ptr <= other.ptr; }
    bool operator>(const DokuVectorIterator& other) const { return ptr > other.ptr; }
    bool operator>=(const DokuVectorIterator& other) const { return ptr >= other.ptr; }
};

#endif //DOKUVECTORITERATOR_H
