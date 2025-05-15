//
// Created by belyashik2k on 5/15/25.
//

#ifndef DOKUSTACK_H
#define DOKUSTACK_H

#include "domain/custom_types/vector/DokuVector.h"

template<typename T>
class DokuStack {
    DokuVector<T> data;
public:
    DokuStack() = default;
    ~DokuStack() = default;

    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (data.empty()) throw std::out_of_range("pop on empty stack");
        data.pop_back();
    }

    T& top() {
        if (data.empty()) throw std::out_of_range("top on empty stack");
        return data[data.size() - 1];
    }

    const T& top() const {
        if (data.empty()) throw std::out_of_range("top on empty stack");
        return data[data.size() - 1];
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }
};
#endif //DOKUSTACK_H
