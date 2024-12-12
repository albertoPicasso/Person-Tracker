#ifndef OBSERVABLELIST_H
#define OBSERVABLELIST_H

#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

template <typename T>
class ObservableList {
private:
    std::queue<T> lifoQueue;
    std::mutex mtx;
    std::condition_variable cv;
    std::vector<std::function<void()>> observers;

public:
    void add(const T& item) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            lifoQueue.push(item);
        }
        cv.notify_all();
        notifyObservers();
    }

    T remove() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !lifoQueue.empty(); });
        T item = lifoQueue.front();
        lifoQueue.pop();
        return item;
    }

    void subscribe(const std::function<void()>& observer) {
        observers.push_back(observer);
    }

private:
    void notifyObservers() {
        for (const auto& observer : observers) {
            observer();
        }
    }
};

#endif // OBSERVABLELIST_H
