//
// Created by anton on 12.11.2019.
//

#include "stretching.h"
#include "hist.h"
#include "Fig.h"
#include "Plotter.h"
#include <algorithm>
#include <opencv4/opencv2/opencv.hpp>

cv::Mat linStretch(const cv::Mat &img);
cv::Mat stableAutoContrast(const cv::Mat &img, const std::vector<int> &hist, int &l, int &r);

void doStretchingExp(const std::vector<Fig> &figs) {
    std::for_each(figs.cbegin(), figs.cend(), [](const Fig &fig) {
        cv::Mat origImg;
        cv::resize(fig.img(), origImg, cv::Size(), 0.25F, 0.25F);

        cv::Mat gray;
        cv::cvtColor(origImg, gray, cv::COLOR_BGR2GRAY);
        auto grayHist = hist(gray);

        cv::Mat overExposed;
        gray.convertTo(overExposed, -1, 1.2F, 1.0F);
        auto overExposedHist = hist(overExposed);

        auto label = std::string("Original_");
        label += fig.name();
        Plotter::showImg(origImg, label);

        label = "Gray_";
        label += fig.name();
        Plotter::showHist(grayHist, label);
        Plotter::showImg(gray, label);

        label = "Gray_stretched_";
        label += fig.name();
        int l, r;
        auto grayStretched = linStretch(gray);
        auto grayStretchedHist = hist(grayStretched);
        Plotter::showHist(grayStretchedHist, label);
        Plotter::showImg(grayStretched, label);

        label = "Gray_stretched_auto_contrast_";
        label += fig.name();
        auto grayAuto = stableAutoContrast(gray, grayHist, l, r);
        auto grayAutoHist = hist(grayAuto);
        Plotter::showHist(grayAutoHist, label);
        Plotter::showImg(grayAuto, label);

        label = "Gray_overexposed_";
        label += fig.name();
        Plotter::showHist(overExposedHist, label);
        Plotter::showImg(overExposed, label);

        label = "Gray_overexposed_stretched_";
        label += fig.name();
        auto grayOverexposedStretched = linStretch(overExposed);
        auto grayOverexposedStretchedHist = hist(grayOverexposedStretched);
        Plotter::showHist(grayOverexposedStretchedHist, label);
        Plotter::showImg(grayOverexposedStretched, label);

        label = "Gray_overexposed_stretched_auto_contrast_";
        label += fig.name();
        auto overExposedStretched = stableAutoContrast(overExposed, overExposedHist, l, r);
        auto overExposedStretchedHist = hist(overExposedStretched);
        Plotter::showHist(overExposedStretchedHist, label);
        Plotter::showImg(overExposedStretched, label);
    });

    cv::waitKey(0);
}

cv::Mat linStretch(const cv::Mat &img) {
    double min;
    double max;
    int minIdx;
    int maxIdx;
    cv::minMaxIdx(img, &min, &max, &minIdx, &maxIdx);

    return (img - min) / (max - min) * 255;
}

cv::Mat stableAutoContrast(const cv::Mat &img, const std::vector<int> &hist, int &l, int &r) {
    auto kPixToLeave = static_cast<int>(img.rows * img.cols * 0.05F);
    auto lBrightness = 0;
    auto rBrightness = 255;
    auto cnt = 0;

    while (lBrightness < rBrightness) {
        if (cnt >= kPixToLeave) {
            break;
        }

        if (hist[lBrightness] < hist[rBrightness]) {
            cnt += hist[lBrightness];
            lBrightness++;
        } else {
            rBrightness--;
            cnt += hist[rBrightness];
        }
    }

    l = lBrightness;
    r = rBrightness;

    return (img - lBrightness) / (rBrightness - lBrightness) * 255;
}
