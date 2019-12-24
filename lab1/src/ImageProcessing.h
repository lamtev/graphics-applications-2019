//
// Created by anton on 23.12.2019.
//

#pragma once

#include <opencv4/opencv2/core/mat.hpp>
#include <vector>

namespace lab1 {
    class ImageProcessing {
    public:
        static std::vector<int> hist(const cv::Mat &img, int dim = 256);

        static cv::Mat stretchLinearly(const cv::Mat &img, int xMin = -1, int xMax = -1);

        static cv::Mat stableAutocontrast(const cv::Mat &img, const std::vector<int> &h, double &lowDropPercent, double &highDropPercent);

        static int cdf(int x, const std::vector<int> &h);

        static std::vector<int> cdf(const std::vector<int> &h);

        static int cdfMin(const std::vector<int> &h);

        static cv::Mat equalize(const cv::Mat &img, const std::vector<int> &h);
    };
}
