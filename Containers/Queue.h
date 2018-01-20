//
// Created by vananiev on 1/5/18.
//

#ifndef HETEROGENEOUSCONTAINER_QUEUE_H
#define HETEROGENEOUSCONTAINER_QUEUE_H

#include <deque>
#include <iostream>
#include <algorithm>


template <typename T>
class Queue;

template <typename T>
class QueueIterator : public BaseIterator<T> {
    typename std::deque<T>::iterator iter;
    typename std::deque<T>::iterator end;

public:
    friend class Queue<T>;

    QueueIterator(typename std::deque<T>::iterator begin, typename std::deque<T>::iterator end) : iter(begin), end(end) {}

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
class Queue : public BaseContainer<T> {
    std::deque<T> queue;

public:
    using Condition = bool (*)(T const&);

    explicit Queue (std::istringstream &iss, int count) {
        for (int i = 0; i < count; i++) {
            T temp;
            iss >> temp;
            add(temp);
        }
    }

    QueueIterator<T> *getIterator() override {
        return new QueueIterator<T>(queue.begin(), queue.end());
    }

    bool member(T const &x) override {
        return std::find(queue.begin(), queue.end(), x) != queue.end();
    }

    void sort() override {
        std::sort(queue.begin(), queue.end());
    }

    void add(T const &x) override {
        queue.emplace_back(x);
    }

    T pop() override {
        T val = queue.back();
        queue.pop_front();
        return val;
    }

    bool hasMember(Condition c) override {
        for (T elem : queue) {
            if (c(elem)) return true;
        }

        return false;
    }

    void filter(Condition c) override {
        std::deque<T> filtered;

        for(T elem : queue) {
            if(!c(elem)) {
                filtered.push_back(elem);
            }
        }

        queue = filtered;
    }

    void print() override {
        std::cout << toString();
    }

    long size() override {
        return queue.size();
    }

    std::string toString() override {
        std::ostringstream str;

        str << size() << " Queue ";

        for (T val : queue) {
            str << val << " ";
        }

        str << '\n';
        return str.str();
    }
};

#endif //HETEROGENEOUSCONTAINER_QUEUE_H
