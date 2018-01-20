//
// Created by vananiev on 1/6/18.
//

#ifndef HETEROGENEOUSCONTAINER_MAINCONTAINER_H
#define HETEROGENEOUSCONTAINER_MAINCONTAINER_H

#include <vector>
#include <fstream>
#include <sstream>
#include "Containers/BaseContainer/BaseContainer.h"
#include "Containers/Queue.h"
#include "Containers/DLinkedList.h"

template<typename T>
class MainContainer;

template<typename T>
class MainIterator : public BaseIterator<T> {
    std::vector<BaseIterator<T> *> iterators;

    BaseIterator<T> *getMinIterator() {
        BaseIterator<T> *min = nullptr;
        typename std::vector<BaseIterator<T> *>::iterator it = iterators.begin();

        while (it != iterators.end()) {
            if((*it)->valid()) {
                if(min == nullptr || min->getData() > (*it)->getData()) {
                    min = *it;
                }
            }
            ++it;
        }

        return min;
    }

public:
    explicit MainIterator(const std::vector<BaseContainer<T> *> &containers) {
        for (BaseContainer<T> *container : containers) {
            iterators.push_back(container->getIterator());
        }
    }

    void next() override {
        BaseIterator<T> *min = getMinIterator();
        if (min) min->next();
    }

    T getData() override {
        BaseIterator<T> *min = getMinIterator();
        return min->getData();
    }

    bool valid() const override {
        for (BaseIterator<T> *iter: iterators) {
            if (iter->valid()) return true;
        }
        return false;
    }
};

template<typename T>
class MainContainer : BaseContainer<T> {
    std::vector<BaseContainer<T> *> containers;

    using Condition = bool (*)(T const &);
    using BC = BaseContainer<T>;
    //TODO: BIG 4

    T pop() override {
        return T();
    }

    void addContainer(BC *cont) {
        containers.push_back(cont);
    }

public:
    void filter(Condition c) override {
        for (BC *container : containers) {
            container->filter(c);
        }
    }

    explicit MainContainer(std::ifstream &file) {
        int n;
        file >> n;

        std::string str;
        while (std::getline(file, str)) {
            std::istringstream iss(str);

            int count;
            std::string type;
            iss >> count >> type;

            if (type == "Stack") {
                BC *s = new Stack<T>(iss, count);
                addContainer(s);
            } else if (type == "Queue") {
                BC *q = new Queue<T>(iss, count);
                addContainer(q);
            } else if (type == "DLinkedList") {
                BC *dll = new DLinkedList<T>(iss, count);
                addContainer(dll);
            }
        }
    }

    MainIterator<T> *getIterator() override {
        sort();
        return new MainIterator<T>(containers);
    }

    MainIterator<T> *iteratorFor(T elem) {
        MainIterator<T> *iter = getIterator();

        while(iter->valid()) {
            if(iter->getData() == elem) {
                return iter;
            }

            iter->next();
        }

        //Iter no longer valid
        return iter;
    }

    void sort() override {
        for (BC *container : containers) {
            container->sort();
        }
    }

    long size() override {
        return containers.size();
    }

    bool hasMember(Condition c) override {
        for (BC *container : containers) {
            if (container->hasMember(c)) return true;
        }

        return false;
    }

    void add(T const &x) override {
        BC *emptiest = *containers.begin();

        for (BC *container : containers) {
            if (container->size() < emptiest->size()) {
                emptiest = container;
            }
        }

        emptiest->add(x);
    }

    void print() {
        std::cout << toString();
    }


    bool member(const T &x) {
        for (auto i = containers.begin(); i != containers.end(); ++i) {
            if ((*i)->member(x)) return true;
        }

        return false;
    }

    std::string toString() {
        std::ostringstream str;

        str << size() << std::endl;

        for (BC *container : containers) {
            str << container->toString();
        }

        return str.str();
    }

    void save(std::ofstream &ofs) {
        ofs << toString();
    }

//    ~MainContainer() = default;
};

#endif //HETEROGENEOUSCONTAINER_MAINCONTAINER_H
