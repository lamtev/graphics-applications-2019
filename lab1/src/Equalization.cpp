//
// Created by anton on 20.12.2019.
//

#include "Equalization.h"
#include "Plotter.h"
#include "ImageProcessing.h"
#include <algorithm>
#include <opencv4/opencv2/opencv.hpp>

using namespace lab1;

void Equalization::doExp(const std::vector<Fig> &figs) {
    std::for_each(figs.cbegin(), figs.cend(), [](const Fig &fig) {
        const cv::Mat& img = fig.img();
        auto hist = ImageProcessing::hist(img);

        auto filename = fig.name();
        filename += "_source";
        Plotter::showHists(hist, ImageProcessing::cdf(hist), "Histogram of source image", filename);
        Plotter::showImg(img, "Source image", filename, false);

        filename = fig.name();
        filename += "_equalized";
        auto equalized = ImageProcessing::equalize(img, hist);
        auto equalizedHist = ImageProcessing::hist(equalized);
        Plotter::showHists(equalizedHist, ImageProcessing::cdf(equalizedHist), "Equalized histogram", filename);
        Plotter::showImg(equalized, "Equalized image", filename, true);
    });

    cv::waitKey(0);
}
