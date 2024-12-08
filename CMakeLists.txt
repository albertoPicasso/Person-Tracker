cmake_minimum_required(VERSION 3.5)
project(YOLO_CXX LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
set(ONNX_RUNTIME_PATH "/opt/onnxruntime")

add_executable(YOLO_CXX videoStreaming)          
target_include_directories(YOLO_CXX PUBLIC
    "${OpenCV_INCLUDE_DIRS}"
    "${ONNX_RUNTIME_PATH}/include")
target_link_directories(YOLO_CXX PUBLIC
    "${ONNX_RUNTIME_PATH}/lib")
target_link_libraries(YOLO_CXX PUBLIC
    ${OpenCV_LIBS}
    "onnxruntime",
    pthreads)