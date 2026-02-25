#pragma once
#include <opencv2/core.hpp>

namespace img {
cv::Mat to_gray(const cv::Mat& bgr);
cv::Mat canny_edges(const cv::Mat& input, double low_threshold, double high_threshold);
} // namepace img
