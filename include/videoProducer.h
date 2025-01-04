#ifndef VIDEOPRODUCER_H
#define VIDEOPRODUCER_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <queue>
#include <iostream>

#include <observableList.h>

class VideoProducer {
    private:
        cv::VideoCapture cap;               
        std::queue<cv::Mat> frameQueue;     
        int maxQueueSize;                   
        int deviceID;                       
        ObservableList<cv::Mat>& list;
        bool &terminate; 

    public:
        VideoProducer(int device, int maxSize, ObservableList<cv::Mat>& frameList, bool &terminate);
        void test(); 
        void captureFrames();
};

#endif 
