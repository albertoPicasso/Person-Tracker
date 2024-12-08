#ifndef CONSUMER_H
#define CONSUMER_H

#include "ObservableList.h"
#include <iostream>

class Consumer {
private:
    ObservableList<int>& list;

public:
    explicit Consumer(ObservableList<int>& observableList) : list(observableList) {
        list.subscribe([this]() { this->onNotification(); });
    }

    void onNotification() {
        int number = list.remove();
        std::cout << "Consumed: " << number << "\n";
    }
};

#endif // CONSUMER_H
