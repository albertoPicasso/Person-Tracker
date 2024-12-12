#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <vector>

using namespace std; 
using namespace cv;
using Array = std::vector<float>;
using Shape = std::vector<long>;
 
class RectangleManagement {
public:
    void mergeRectangles(std::vector<cv::Rect>& rects) {
        bool isTrue = false;  // Changed 'False' to 'false'
        
        // Compare each rectangle with the others
        for (int i = 0; i < rects.size(); ++i) {
            for (int j = i + 1; j < rects.size(); ++j) {  
                isTrue = isInside(rects[i], rects[j]);
                if (isTrue) {
                    rects.erase(rects.begin() + j);
                    --j;
                }
            }
        }
    }

private:
    bool isInside(const Rect& r1, const Rect& r2) {
        // Check if the coordinates of r2 are inside r1
        return (r2.x >= r1.x) && (r2.y >= r1.y) && 
               (r2.x + r2.width <= r1.x + r1.width) &&
               (r2.y + r2.height <= r1.y + r1.height);
    }
};

int main() {
    std::string imagePath = "images/gente.png";
    
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error loading the image!" << std::endl;
        return -1;
    }

    // Create a HOG descriptor
    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

    // Detect people
    std::vector<cv::Rect> found, found_filtered;
    hog.detectMultiScale(image, found, 0, Size(8, 8), Size(), 1.05, 2, false); // Detection threshold and grouping

    // Create a RectangleManagement object
    RectangleManagement rm; 

    // Call the rectangle merging function
    rm.mergeRectangles(found);

    // Draw the detections on the image
    for (size_t i = 0; i < found.size(); i++) {
        cv::rectangle(image, found[i], cv::Scalar(0, 255, 0), 3);
    }

    // Display the image with detections
    cv::imshow("People Detection", image);
    cv::waitKey(0);
    return 0;
}
