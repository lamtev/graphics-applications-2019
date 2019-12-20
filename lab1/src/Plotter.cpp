//
// Created by anton on 20.12.2019.
//

#include "Plotter.h"
#include "matplotlibcpp.h"
#include <opencv4/opencv2/opencv.hpp>

namespace plt = matplotlibcpp;

void Plotter::showImg(const cv::Mat &img, const std::string &label) {
    cv::Mat im;
    cv::resize(img, im, cv::Size(), 0.9F, 0.9F);
    cv::namedWindow(label, cv::WINDOW_AUTOSIZE);
    cv::imshow(label, im);
}

void Plotter::showHist(const std::vector<int> &hist, const std::string &label, int l, int r) {
    plt::plot(hist);
    if (l != -1 && r != -1) {
        std::vector<double> lx(100, static_cast<double>(l));
        std::vector<double> rx(100, static_cast<double>(r));
        std::vector<double> y;
        double yMax = *std::max_element(hist.cbegin(), hist.cend());
        for (int i = 0; i < 100; ++i) {
            y.push_back(i * (yMax / 100));
        }

        plt::plot(lx, y);
        plt::plot(rx, y);
    }
    plt::title(label);
    auto fileName = label;
    fileName += "_hist";
    plt::save(fileName);
    plt::close();
}

void Plotter::showHists(const std::vector<int> &hist1, const std::vector<int> &hist2, const std::string &label) {
    plt::plot(hist1);
    plt::plot(hist2);
    plt::title(label);
    auto fileName = label;
    fileName += "_hist";
    plt::save(fileName);
    plt::close();
}
