//
// Created by anton on 20.12.2019.
//

#include "equalization.h"
#include "hist.h"
#include "Plotter.h"
#include <algorithm>
#include <opencv4/opencv2/opencv.hpp>

std::vector<int> cumulativeSum(const std::vector<int> &hist);
std::vector<int> cdfNorm(const std::vector<int> &cdf, const std::vector<int> &hist);
cv::Mat equalize(const cv::Mat &img, const std::vector<int> &hist);

void doEqualizationExp(const std::vector<Fig> &figs) {
    std::for_each(figs.cbegin(), figs.cend(), [](const Fig &fig) {
        cv::Mat origImg;
        cv::resize(fig.img(), origImg, cv::Size(), 0.25F, 0.25F);

        cv::Mat gray;
        cv::cvtColor(origImg, gray, cv::COLOR_BGR2GRAY);
        auto grayHist = hist(gray);

        auto grayCdf = cumulativeSum(grayHist);
        auto grayCdfNorm = cdfNorm(grayCdf, grayHist);

        std::string label = "Gray_";
        label += fig.name();
        Plotter::showHists(grayHist, grayCdfNorm, label);
        Plotter::showImg(gray, label);

        auto grayEqualized = equalize(gray, grayCdf);
        auto grayEqualizedHist = hist(grayEqualized);
        auto grayEqualizedCdf = cumulativeSum(grayEqualizedHist);
        auto grayEqualizedCdfNorm = cdfNorm(grayEqualizedCdf, grayEqualizedHist);

        label = "Gray_equalized_";
        label += fig.name();
        Plotter::showHists(grayEqualizedHist, grayEqualizedCdfNorm, label);
        Plotter::showImg(grayEqualized, label);
    });

    cv::waitKey(0);
}

std::vector<int> cumulativeSum(const std::vector<int> &hist) {
    std::vector<int> cdf(hist);
    for (auto i = 1; i < hist.size(); ++i) {
        cdf[i] += hist[i - 1];
    }

    return cdf;
}

std::vector<int> cdfNorm(const std::vector<int> &cdf, const std::vector<int> &hist) {
    std::vector<int> cdfNorm(cdf);
    auto normCoefficient = (*std::max_element(hist.cbegin(), hist.cend())) /*/ (*std::max_element(cdf.cbegin(), cdf.cend()))*/;
    for (auto i = 0; i < cdf.size(); ++i) {
        cdfNorm[i] /= normCoefficient;
    }

    return cdfNorm;
}

cv::Mat equalize(const cv::Mat &img, const std::vector<int> &hist) {
    auto cdfMin = *std::upper_bound(hist.cbegin(), hist.cend(), 0.0F);
    auto cdfMax = img.rows * img.cols;
    auto res = img.clone();

    for (int i = 0; i < res.rows; ++i) {
        for (int j = 0; j < res.cols; ++j) {
            auto newVal = round((double) (hist[res.at<uchar>(i, j)] - cdfMin) / cdfMax * 255);
            res.at<uchar>(i, j) = newVal;
        }
    }

    return res;
}
