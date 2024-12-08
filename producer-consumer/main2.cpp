#include "ObservableList.h"
#include "Producer.h"
#include "Consumer.h"
#include <thread>
#include <chrono>

int main() {
    ObservableList<int> observableList;

    // Crear productor y consumidor
    Producer producer(observableList);
    Consumer consumer(observableList);

    // Crear hilo del productor
    std::thread producerThread([&producer]() {
        for (int i = 1; i <= 10; ++i) {
            producer.produce(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simula el tiempo de producción
        }
    });

    // Crear hilo del consumidor
    std::thread consumerThread([&consumer]() {
        // El consumidor está escuchando notificaciones y consumiendo datos
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Esperamos un poco antes de empezar
    });

    // Esperar que ambos hilos terminen
    producerThread.join();
    consumerThread.join();

    return 0;
}
