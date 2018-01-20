#include <iostream>
#include "Containers/Stack.h"
#include "MainContainer.h"
#include "Containers/DLinkedList.h"
#include "Containers/Queue.h"

bool odd(const int &x) {
    return x % 2 == 1;
}

int main() {

    std::ifstream file("../test.txt");

    MainContainer<int> cont(file);

    cont.filter(odd);
    cont.add(3);

    cont.print();

    std::cout << std::endl << "Sorted Iterator" << std::endl;
    BaseIterator<int> *iter = cont.getIterator();
    while (iter->valid()) {
        std::cout << iter->getData() << ", ";
        iter->next();
    }

    std::cout << std::endl << std::endl << "Iterator after 60" << std::endl;
    BaseIterator<int> *itAfter = cont.iteratorFor(60);
    while (itAfter->valid()) {
        std::cout << itAfter->getData() << ", ";
        itAfter->next();
    }

    std::cout << std::endl << std::endl << "Iterator after 55 (Not in container)" << std::endl;
    BaseIterator<int> *itAfterInvalid = cont.iteratorFor(55);
    if (itAfterInvalid->valid()) {
        while (itAfter->valid()) {
            std::cout << itAfter->getData() << ", ";
            itAfter->next();
        }
    } else {
        std::cout << "INVALID iterator :)" << std::endl;
    }


    std::cout << std::endl << "Serialize" << std::endl;
    cont.print();
    std::ofstream output("output.txt");
    cont.save(output);
    return 0;
}