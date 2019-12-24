//
// Created by anton on 20.12.2019.
//

#pragma once

#include <vector>
#include <string>
#include <opencv4/opencv2/core/mat.hpp>

class Plotter {
public:
    static void showImg(const cv::Mat &img, const std::string &label, const std::string &filename, bool save = false);
    static void saveImg(const cv::Mat &img, const std::string &fileName);
    static void showHist(const std::vector<int> &hist, const std::string &label, const std::string &filename, bool save = true, int l = -1, int r = -1);
    static void showHists(const std::vector<int> &h, const std::vector<int> &cdf, const std::string &label, const std::string &filename, bool save = true);
};

