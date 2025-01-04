#include "videoProducer.h"

using namespace cv;
using namespace std;


VideoProducer::VideoProducer(int device, int maxSize, ObservableList<cv::Mat>& frameList, bool &terminate)
    : deviceID(device), maxQueueSize(maxSize), cap(device), list(frameList),terminate (terminate) {
    
    
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        exit(-1); 
    }
    
}

void VideoProducer::test() {
    cv::Mat test; 
    list.add(test); 
}

void VideoProducer::captureFrames() {
    cv::Mat frame;

    while (1) {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        //imshow("Live", frame);
        int key = cv::waitKey(5); // Espera 5 ms por una tecla

        // Si el usuario presiona 's' o 'S', salimos del bucle
        if (key == 's' || key == 'S') {
            std::cout << "Programa detenido por la tecla 'S'." << std::endl;
            break;
        }
        list.add(frame);
    }
}
