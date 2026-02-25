#include "image_ops.hpp"
#include <opencv2/imgproc.hpp>
#include <stdexcept>

namespace img {
cv::Mat to_gray(const cv::Mat& bgr) {
    if (bgr.empty()) {
        throw std::invalid_argument("Input image is empty");
    }

    cv::Mat gray;
    if (bgr.channels() == 1) {
        // Already grayscale
        gray = bgr.clone();
    } else if (bgr.channels() == 3) {
        cv::cvtColor(bgr, gray, cv::COLOR_BGR2GRAY);
    } else if (bgr.channels() == 4) {
        cv::cvtColor(bgr, gray, cv::COLOR_BGRA2GRAY);
    } else {
        throw std::invalid_argument("Unsupported number of channels: " + std::to_string(bgr.channels()));
    }
    return gray;
}

cv::Mat canny_edges(const cv::Mat& input, double low_threshold, double high_threshold) {
    if (input.empty()) {
        throw std::invalid_argument("Input image is empty");
    }

    if (low_threshold <= 0 || high_threshold <= 0 || low_threshold >= high_threshold) {
        throw std::invalid_argument("Thresholds invalid: 0 < low_threshold < high_threshold");
    }

    cv::Mat gray = to_gray(input);
    cv:: Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 1.2);

    cv::Mat edges;
    cv::Canny(blurred, edges, low_threshold, high_threshold);
    return edges;
}

} // namespace img

