#ifndef VIDEOPRODUCER_H
#define VIDEOPRODUCER_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <queue>
#include <iostream>

class VideoProducer {
private:
    cv::VideoCapture cap;               // Captura de video
    std::queue<cv::Mat> frameQueue;     // Cola de fotogramas
    int maxQueueSize;                   // Tamaño máximo de la cola
    int deviceID;                       // ID del dispositivo de cámara

public:
    // Constructor
    VideoProducer(int device = 0, int maxSize = 10);

    // Método para capturar frames
    void captureFrames();
};

#endif // VIDEOPRODUCER_H
