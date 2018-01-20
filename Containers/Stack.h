//
// Created by vananiev on 1/5/18.
//

#ifndef HETEROGENEOUSCONTAINER_STACK_H
#define HETEROGENEOUSCONTAINER_STACK_H

#include "BaseContainer/BaseContainer.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>


template <typename T>
class Stack;

template <typename T>
class StackIterator : public BaseIterator<T> {
    typename std::deque<T>::iterator iter;
    typename std::deque<T>::iterator end;

public:
    friend class Stack<T>;

    StackIterator(typename std::deque<T>::iterator begin, typename std::deque<T>::iterator end) : iter(begin), end(end) {}

    void next() override {
        ++iter;
    }

    bool valid() const override {
        return iter != end;
    }

    T getData() override {
        return *iter;
    }
};

template<typename T>
class Stack : public BaseContainer<T> {
    std::deque<T> stack;
public:
    using Condition = bool (*)(T const &);

    explicit Stack(std::istringstream &iss, int count) {
        for (int i = 0; i < count; i++) {
            T temp;
            iss >> temp;
            add(temp);
        }
    }

    StackIterator<T> *getIterator() override {
        return new StackIterator<T>(stack.begin(), stack.end());
    }

    bool member(const T &x) override {
        return std::find(stack.begin(), stack.end(), x) != stack.end();
    }

    void sort() override {
        std::sort(stack.begin(), stack.end());
    }

    void add(const T &x) override {
        stack.emplace_back(x);
    }

    T pop() override {
        T val = stack.back();
        stack.pop_back();
        return val;
    }

    bool hasMember(Condition c) override {
        for (T elem : stack) {
            if (c(elem)) return true;
        }

        return false;
    }

    void filter(Condition c) override {
        std::deque<T> filtered;

        for(T elem : stack) {
            if(!c(elem)) {
                filtered.push_back(elem);
            }
        }

        stack = filtered;
    }

    void print() override {
        std::cout << toString();
    }

    long size() override {
        return stack.size();
    }

    std::string toString() override {
        std::ostringstream str;

        str << size() << " Stack ";

        for (T val : stack) {
            str << val << " ";
        }

        str << '\n';
        return str.str();
    }
};

#endif //HETEROGENEOUSCONTAINER_STACK_H
