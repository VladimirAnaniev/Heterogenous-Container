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
    std::ofstream output("output.txt");
    cont.save(output);
    return 0;
}