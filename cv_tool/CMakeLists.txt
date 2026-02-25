cmake_minimum_required(VERSION 3.16)
project(cv_tool VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(cv_tool
    src/main.cpp
    src/image_ops.cpp
)

target_include_directories(cv_tool PRIVATE include)
target_link_libraries(cv_tool PRIVATE opencv_core opencv_imgproc opencv_imgcodecs)

if (MSVC)
  add_compile_options(cv_tool PRIVATE /W4)
else()
  add_compile_options(cv_tool PRIVATE -Wall -Wextra -Wpedantic)
endif()

message(STATUS "OpenCV version: ${OpenCV_VERSION}")
