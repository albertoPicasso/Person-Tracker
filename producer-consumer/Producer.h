#ifndef PRODUCER_H
#define PRODUCER_H

#include "ObservableList.h"
#include <iostream>

class Producer {
private:
    ObservableList<int>& list;

public:
    explicit Producer(ObservableList<int>& observableList) : list(observableList) {}

    void produce(int number) {
        std::cout << "Producing: " << number << "\n";
        list.add(number);
    }
};

#endif // PRODUCER_H
