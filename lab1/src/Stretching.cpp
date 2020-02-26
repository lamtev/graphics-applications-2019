//
// Created by anton on 12.11.2019.
//

#include "Stretching.h"
#include "ImageProcessing.h"
#include "Fig.h"
#include "Plotter.h"
#include <algorithm>
#include <opencv4/opencv2/opencv.hpp>

using namespace lab1;

void Stretching::doExp(const std::vector<Fig> &figs) {
    std::for_each(figs.cbegin(), figs.cend(), [](const Fig &fig) {
        const cv::Mat& img = fig.img();
        auto hist = ImageProcessing::hist(img);

        auto filename = fig.name();
        filename += "_stretch_source";
        Plotter::showHist(hist, "Histogram of source image", filename);
        Plotter::showImg(img, "Source image", filename, false);

        filename = fig.name();
        filename += "_stretch_stretched";
        auto stretched = ImageProcessing::stretchLinearly(img);
        auto stretchedHist = ImageProcessing::hist(stretched);
        Plotter::showHist(stretchedHist, "Histogram after linear stretching", filename);
        Plotter::showImg(stretched, "Image after linear stretching", filename, true);

        filename = fig.name();
        filename += "_stretch_stretched_with_bounds";
        double low = fig.lowDropBound();
        double high = fig.highDropBound();
        auto withBounds = ImageProcessing::stableAutocontrast(img, hist, low, high);
        auto withBoundsHist = ImageProcessing::hist(withBounds);
        Plotter::showHist(withBoundsHist, "Histogram after bounded linear stretching", filename, true, low, high);
        Plotter::showImg(withBounds, "Image after bounded linear stretching", filename, true);
    });

    cv::waitKey(0);
}
