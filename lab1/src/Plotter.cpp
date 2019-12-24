//
// Created by anton on 20.12.2019.
//

#include "Plotter.h"
#include "matplotlibcpp.h"
#include <opencv4/opencv2/opencv.hpp>

namespace plt = matplotlibcpp;

void Plotter::showImg(const cv::Mat &img, const std::string &label, const std::string &filename, bool save) {
    if (save) {
        saveImg(img, filename);
    }
    cv::namedWindow(filename, cv::WINDOW_AUTOSIZE);
    cv::imshow(filename, img);
}

void Plotter::saveImg(const cv::Mat &img, const std::string &fileName) {
    std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 100};
    cv::imwrite(fileName + ".jpg", img, params);
}

void Plotter::showHist(const std::vector<int> &hist, const std::string &label, const std::string &filename, bool save, int l, int r) {
    plt::plot(hist);
    if (l != -1 && r != -1) {
        std::vector<double> lx(100, static_cast<double>(l));
        std::vector<double> rx(100, static_cast<double>(r));
        std::vector<double> y;
        double yMax = *std::max_element(hist.cbegin(), hist.cend());
        for (int i = 0; i < 100; ++i) {
            y.push_back(i * (yMax / 100));
        }

        plt::plot(lx, y, "r");
        plt::plot(rx, y, "r");
    }
    plt::title(label);
    auto fileName = filename;
    fileName += "_hist";
    if (save) {
        plt::save(fileName);
    }
    plt::close();
}

void Plotter::showHists(const std::vector<int> &h, const std::vector<int> &cdf, const std::string &label, const std::string &filename, bool save) {
    plt::named_plot("h", h, "b");
    plt::named_plot("cdf", cdf, "r");
    plt::legend();
    plt::title(label);
    auto fileName = filename;
    fileName += "_hists";
    if (save) {
        plt::save(fileName);
    }
    plt::close();
}
