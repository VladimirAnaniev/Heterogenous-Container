//
// Created by vananiev on 1/5/18.
//

#ifndef HETEROGENEOUSCONTAINER_DLINKEDLIST_H
#define HETEROGENEOUSCONTAINER_DLINKEDLIST_H

#include <deque>
#include <algorithm>
#include <iostream>
#include <sstream>

template<typename T>
class DLinkedList : public BaseContainer<T> {
    std::deque<T> dllist;

public:
    using Condition = bool (*)(T const &);

    explicit DLinkedList(std::istringstream &iss, int count) {
        for (int i = 0; i < count; i++) {
            T temp;
            iss >> temp;
            add(temp);
        }
    }

    bool member(T const &x) override {
        return std::find(dllist.begin(), dllist.end(), x) != dllist.end();
    }

    void sort() override {
        std::sort(dllist.begin(), dllist.end());
    }

    void add(T const &x) override {
        dllist.emplace_back(x);
    }

    T pop() override {
        T val = dllist.front();
        dllist.pop_front();
        return val;
    }

    bool hasMember(Condition c) override {
        for (T elem : dllist) {
            if (c(elem)) return true;
        }

        return false;
    }

    void filter(Condition c) override {
        std::deque<T> filtered;

        for(T elem : dllist) {
            if(!c(elem)) {
                filtered.push_back(elem);
            }
        }

        dllist = filtered;
    }

    void print() override {
        std::cout << toString();
    }

    long size() override {
        return dllist.size();
    }

    std::string toString() override {
        std::ostringstream str;

        str << size() << " DLinkedList ";

        for (T val : dllist) {
            str << val << " ";
        }

        str << '\n';
        return str.str();
    }
};

#endif //HETEROGENEOUSCONTAINER_DLINKEDLIST_H
