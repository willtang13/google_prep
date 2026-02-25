#include "image_ops.hpp"
#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <string>

static void print_usage() {
    std::cout
        << "Usage: " 
        << " cv_tool <input_image> <output_image> [--mode gray|canny] [--lt <low_threshold> N] [--ht <high_threshold> N]\n\n"
        << "Examples:\n"
        << "  cv_tool input.jpg gray.jpg --mode gray\n"
        << "  cv_tool input.jpg edge.jpg --mode canny --lt 50 --ht 150\n";
}

int main(int argc, char** argv) {
    if (argc < 3) {
        print_usage();
        return 1;
    }
    std::string input_path = argv[1];
    std::string output_path = argv[2];

    std::string mode = "gray";
    double low_threshold = 50.0;
    double high_threshold = 150.0;

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--mode" && i + 1 < argc) {
            mode = argv[++i];
        } else if (arg == "--lt" && i + 1 < argc) {
            low_threshold = std::stod(argv[++i]);
        } else if (arg == "--ht" && i + 1 < argc) {
            high_threshold = std::stod(argv[++i]);
        } else if (arg == "--help" || arg == "-h") {
            print_usage();
            return 0;
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            print_usage();
            return 1;
        }
    }

    cv::Mat input_image = cv::imread(input_path, cv::IMREAD_COLOR);
    if (input_image.empty()) {
        std::cerr << "Failed to load image: " << input_path << std::endl;
        return 1;
    }

    try {
        auto start_time = std::chrono::steady_clock::now();
        cv::Mat output_image;
        if (mode == "gray") {
            output_image = img::to_gray(input_image);
        } else if (mode == "canny") {
            output_image = img::canny_edges(input_image, low_threshold, high_threshold);
        } else {
            std::cerr << "Unknown mode: " << mode << std::endl;
            print_usage();
            return 1;
        }
        auto end_time = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

        if (!cv::imwrite(output_path, output_image)) {
            std::cerr << "Failed to save image: " << output_path << std::endl;
            return 1;
        }

        std::cout << "OK\n"
                  << "Mode: " << mode << "\n"
                  << "Input: " << input_path << " (WxH=" << input_image.cols << "x" << input_image.rows
                  << ", ch=" << input_image.channels() << ")\n"
                  << "Output: " << output_path << "\n"
                  << "Time: " << ms << " ms\n";

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}