//
// Created by anton on 20.12.2019.
//

#pragma once

#include <opencv4/opencv2/core/mat.hpp>
#include <vector>

std::vector<int> hist(const cv::Mat &fig, int dim = 256);
