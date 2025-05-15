//
// Created by belyashik2k on 5/15/25.
//

#ifndef DOKUVECTOR_H
#define DOKUVECTOR_H

#include <stdexcept>
#include <algorithm>

#include "DokuVectorIterator.h"

template<typename T>
class DokuVector {
    T* data;
    size_t _size;
    size_t _capacity;

    void reallocate(const size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i)
            new_data[i] = std::move(data[i]);
        delete[] data;
        data = new_data;
        _capacity = new_capacity;
    }

public:
    DokuVector() : data(nullptr), _size(0), _capacity(0) {}

    ~DokuVector() {
        delete[] data;
    }

    DokuVector(const DokuVector &other)
        : data(new T[other._capacity]), _size(other._size), _capacity(other._capacity) {
        std::copy(other.data, other.data + _size, data);
    }

    DokuVector& operator=(const DokuVector &other) {
        if (this != &other) {
            delete[] data;
            _size = other._size;
            _capacity = other._capacity;
            data = new T[_capacity];
            std::copy(other.data, other.data + _size, data);
        }
        return *this;
    }

    DokuVector(DokuVector &&other) noexcept
        : data(other.data), _size(other._size), _capacity(other._capacity) {
        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    DokuVector& operator=(DokuVector &&other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            _size = other._size;
            _capacity = other._capacity;
            other.data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    void push_back(const T &value) {
        if (_size == _capacity) {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        data[_size++] = value;
    }

    void pop_back() {
        if (_size == 0) throw std::out_of_range("Vector empty");
        --_size;
    }

    void clear() {
        _size = 0;
    }

    void reserve(const size_t new_capacity) {
        if (new_capacity > _capacity)
            reallocate(new_capacity);
    }

    void resize(const size_t new_size, const T& value = T()) {
        if (new_size > _capacity)
            reallocate(new_size);
        for (size_t i = _size; i < new_size; ++i)
            data[i] = value;
        _size = new_size;
    }

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    T& operator[](const size_t index) {
        return at(index);
    }
    const T& operator[](const size_t index) const {
        return at(index);
    }

    T& at(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    using iterator = DokuVectorIterator<T>;

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + _size); }

    iterator begin() const { return iterator(data); }
    iterator end() const { return iterator(data + _size); }
};

#endif //DOKUVECTOR_H
