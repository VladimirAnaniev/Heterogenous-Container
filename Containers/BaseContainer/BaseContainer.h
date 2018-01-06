//
// Created by vananiev on 1/5/18.
//

#ifndef HETEROGENEOUSCONTAINER_BASECONTAINER_H
#define HETEROGENEOUSCONTAINER_BASECONTAINER_H

template <typename T>
class BaseContainer {
public:
    using Condition = bool (*)(T const&);

    virtual bool member(T const& x) = 0;

    virtual void sort() = 0;

    virtual void add(T const& x) = 0;

    virtual T pop() = 0;

    virtual bool hasMember(Condition c) = 0;

    virtual void filter(Condition c) = 0;

    virtual void print() = 0;

    virtual long size() = 0;

    virtual std::string toString() = 0;

    virtual ~BaseContainer() = default;
};


#endif //HETEROGENEOUSCONTAINER_BASECONTAINER_H
