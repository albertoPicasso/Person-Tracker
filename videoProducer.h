#ifndef VIDEOPRODUCER_H
#define VIDEOPRODUCER_H
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <queue>
#include <iostream>
#include <stdio.h>


using namespace cv;
using namespace std;

class VideoProducer {
private:
    cv::VideoCapture cap;               
    std::queue<Mat> frameQueue;          
    int maxQueueSize;               
    int deviceID;                   

public:

    VideoProducer(int device = 0, int maxSize = 10)
    :deviceID(device), maxQueueSize(maxSize) 
    {
        if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        exit(-1); 
    }

    }

    void captureFrames (){
        cv::Mat frame; 
    
        while (1){
            
            cap.read(frame);
            
            if (frame.empty()) {
                cerr << "ERROR! Blank frame grabbed\n";
                break;
            }

            if (frameQueue.size() >= maxQueueSize) {
                frameQueue.pop();  
            }
            frameQueue.push(frame);

        }

    }


};  

#endif // VIDEOPRODUCER_H