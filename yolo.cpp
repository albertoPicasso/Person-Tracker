#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <cassert>

using Array = std::vector<float>;
using Shape = std::vector<long>;


const char *class_names[] = {
    "person",         "bicycle",    "car",           "motorcycle",    "airplane",     "bus",           "train",
    "truck",          "boat",       "traffic light", "fire hydrant",  "stop sign",    "parking meter", "bench",
    "bird",           "cat",        "dog",           "horse",         "sheep",        "cow",           "elephant",
    "bear",           "zebra",      "giraffe",       "backpack",      "umbrella",     "handbag",       "tie",
    "suitcase",       "frisbee",    "skis",          "snowboard",     "sports ball",  "kite",          "baseball bat",
    "baseball glove", "skateboard", "surfboard",     "tennis racket", "bottle",       "wine glass",    "cup",
    "fork",           "knife",      "spoon",         "bowl",          "banana",       "apple",         "sandwich",
    "orange",         "broccoli",   "carrot",        "hot dog",       "pizza",        "donut",         "cake",
    "chair",          "couch",      "potted plant",  "bed",           "dining table", "toilet",        "tv",
    "laptop",         "mouse",      "remote",        "keyboard",      "cell phone",   "microwave",     "oven",
    "toaster",        "sink",       "refrigerator",  "book",          "clock",        "vase",          "scissors",
    "teddy bear",     "hair drier", "toothbrush"};
/*
const char *class_names[] = {
    "person"};
    **/
std::tuple<Array, Shape, cv::Mat> read_image(const std::string &path, int size)
{
    auto image = cv::imread(path);
    assert(!image.empty() && image.channels() == 3);
    cv::resize(image, image, {size, size});
    Shape shape = {1, image.channels(), image.rows, image.cols};
    cv::Mat nchw = cv::dnn::blobFromImage(image, 1.0, {}, {}, true) / 255.f;
    Array array(nchw.ptr<float>(), nchw.ptr<float>() + nchw.total());
    return {array, shape, image};
}

std::pair<Array, Shape> process_image(Ort::Session &session, Array &array, Shape shape)
{
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    auto input = Ort::Value::CreateTensor<float>(
        memory_info, (float *)array.data(), array.size(), shape.data(), shape.size());

    const char *input_names[] = {"images"};
    const char *output_names[] = {"output"};
    auto output = session.Run({}, input_names, &input, 1, output_names, 1);
    shape = output[0].GetTensorTypeAndShapeInfo().GetShape();
    auto ptr = output[0].GetTensorData<float>();
    return {Array(ptr, ptr + shape[0] * shape[1]), shape};
}

void display_image(cv::Mat image, const Array &output, const Shape &shape)
{
    for (size_t i = 0; i < shape[0]; ++i)
    {
        auto ptr = output.data() + i * shape[1];
        int x = ptr[1], y = ptr[2], w = ptr[3] - x, h = ptr[4] - y, c = ptr[5];
        auto color = CV_RGB(255, 255, 255);
        auto name = std::string(class_names[c]) + ":" + std::to_string(int(ptr[6] * 100)) + "%";
        cv::rectangle(image, {x, y, w, h}, color);
        cv::putText(image, name, {x, y}, cv::FONT_HERSHEY_DUPLEX, 1, color);
    }

    cv::imshow("YOLOv7 Output", image);
    cv::waitKey(0);
}

int main() {

    bool use_cuda = true;
    int image_size = 640;
    std::string model_path = "/home/al/Escritorio/horus/model/yolov7-tiny.onnx";
    std::string image_path = "gente.png";

    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "YOLOv7");
    Ort::SessionOptions options;
    Ort::Session session(env, model_path.c_str(), options);
    
    auto image = read_image(image_path, image_size); 
    
    // Desempaquetar los valores del tuple
    Array array = std::get<0>(image);  // Primer elemento del tuple (Array)
    Shape shape = std::get<1>(image);  // Segundo elemento del tuple (Shape)
    cv::Mat images = std::get<2>(image); 

    auto processed_result = process_image(session, array, shape);
    Array output_array = processed_result.first;
    Shape output_shape = processed_result.second;
    
    display_image(images, output_array, output_shape);   
    return 0;
}