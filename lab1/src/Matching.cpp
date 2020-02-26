//
// Created by anton on 22.01.2020.
//

#include "Matching.h"
#include "Fig.h"
#include "Plotter.h"
#include "ImageProcessing.h"
#include <algorithm>
#include <opencv4/opencv2/opencv.hpp>

void lab1::Matching::doExp(const Fig &ref, const std::vector<Fig> &figs) {
    std::for_each(figs.cbegin(), figs.cend(), [&ref](const Fig &fig) {
        const cv::Mat& img = fig.img();
        auto hist = ImageProcessing::hist(img);

        auto filename = fig.name();
        filename += "_source";
        Plotter::showHists(hist, ImageProcessing::cdf(hist), "Histogram of source image", filename);
        Plotter::showImg(img, "Source image", filename, false);

        filename = ref.name();
        filename += "_ref";
        const auto& reference = ref.img();
        auto referenceHist = ImageProcessing::hist(reference);
        Plotter::showHists(referenceHist, ImageProcessing::cdf(referenceHist), "Reference histogram", filename);
        Plotter::showImg(reference, "Reference image", filename, true);

        filename = fig.name();
        filename += "_matched";
        auto matched = ImageProcessing::match(img, reference);
        auto matchedHist = ImageProcessing::hist(matched);
        Plotter::showHists(matchedHist, ImageProcessing::cdf(matchedHist), "Matched histogram", filename);
        Plotter::showImg(matched, "Matched image", filename, true);
    });

    cv::waitKey(0);
}
