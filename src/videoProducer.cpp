#include "videoProducer.h"

using namespace cv;
using namespace std;

// Constructor
VideoProducer::VideoProducer(int device, int maxSize)
    : deviceID(device), maxQueueSize(maxSize), cap(device) {
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        exit(-1); 
    }
}

// Método para capturar frames
void VideoProducer::captureFrames() {
    cv::Mat frame;

    while (1) {
        cap.read(frame);

        if (frame.empty()) {
            cerr << "ERROR! Blank frame grabbed\n";
            break;
        }

        if (frameQueue.size() >= maxQueueSize) {
            frameQueue.pop();  // Elimina el fotograma más antiguo
        }
        frameQueue.push(frame);
    }
}
