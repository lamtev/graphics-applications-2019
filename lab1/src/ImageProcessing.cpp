//
// Created by anton on 23.12.2019.
//

#include "ImageProcessing.h"
#include <opencv4/opencv2/opencv.hpp>
#include <algorithm>

using namespace lab1;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
std::vector<int> ImageProcessing::hist(const cv::Mat &img, int dim) {
    std::vector<int> h(dim, 0);
    for (auto el = img.begin<uchar>(); el != img.end<uchar>(); ++el) {
        ++h[*el];
    }

    return h;
}
#pragma clang diagnostic pop

cv::Mat ImageProcessing::stretchLinearly(const cv::Mat &img, int xMin, int xMax) {
    auto stretched = img.clone();

    double _xMin;
    double _xMax;

    if (xMin == -1 && xMax == -1) {
        cv::minMaxIdx(stretched, &_xMin, &_xMax);
    } else {
        _xMin = xMin;
        _xMax = xMax;
    }

    return (stretched - _xMin) * 255 / (_xMax - _xMin);
}

cv::Mat ImageProcessing::stableAutocontrast(const cv::Mat &img, const std::vector<int> &h, double &lowDropPercent, double &highDropPercent) {
    auto nLowPixelsToDrop = static_cast<int>(round(static_cast<double>(img.rows * img.cols) * lowDropPercent / 100.0));
    auto nHighPixelsToDrop = static_cast<int>(round(static_cast<double>(img.rows * img.cols) * highDropPercent / 100.0));
    auto lowCount = 0;
    auto highCount = 0;
    auto xMin = 0;
    auto xMax = 0;

    for (auto lowI = 0, highI = static_cast<int>(h.size()); lowI < h.size(); ++lowI, --highI) {
        if (xMin * xMax != 0) {
            break;
        }

        lowCount += h[lowI];
        if (xMin == 0 && lowCount > nLowPixelsToDrop) {
            xMin = lowI;
        }

        highCount += h[highI];
        if (xMax == 0 && highCount > nHighPixelsToDrop) {
            xMax = highI;
        }
    }

    lowDropPercent = xMin;
    highDropPercent = xMax;

    return stretchLinearly(img, xMin, xMax);
}

int ImageProcessing::cdf(int x, const std::vector<int> &h) {
    auto _cdf = 0;
    for (auto i = 0; i <= x; ++i) {
        _cdf += h[i];
    }

    return _cdf;
}

std::vector<int> ImageProcessing::cdf(const std::vector<int> &h) {
    std::vector<int> _cdf;
    _cdf.reserve(h.size());

    for (auto i = 0; i < h.size(); ++i) {
        _cdf.push_back(cdf(i, h));
    }

    auto hMax = *std::max_element(h.cbegin(), h.cend());
    auto cdfMax = *std::max_element(_cdf.cbegin(), _cdf.cend());
    auto cdfMin = *std::min_element(_cdf.cbegin(), _cdf.cend());

    for (auto &e : _cdf) {
        e *= ((double) hMax / (cdfMax - cdfMin));
    }

    return _cdf;
}

int ImageProcessing::cdfMin(const std::vector<int> &h) {
    auto _cdfMinIt = std::find_if(h.cbegin(), h.cend(), [](int x) {
        return x > 0;
    });

    return _cdfMinIt != h.cend() ? *_cdfMinIt : 0;
}

std::vector<float> ImageProcessing::cdfNorm(const std::vector<int> &h) {
    auto max = *std::max_element(h.cbegin(), h.cend());
    std::vector<float> copy;
    copy.reserve(h.size());
    copy.insert(copy.cbegin(), h.cbegin(), h.cend());
    for (auto &el : copy) {
        el /= (float) max;
    }
    return copy;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
cv::Mat ImageProcessing::equalize(const cv::Mat &img, const std::vector<int> &h) {
    auto pixelCount = img.rows * img.cols;
    auto cdfMin = ImageProcessing::cdfMin(h);

    auto equalized = img.clone();

    for (auto el = equalized.begin<uchar>(); el != equalized.end<uchar>(); ++el) {
        *el = static_cast<uchar>(round(static_cast<double>((cdf(*el, h) - cdfMin) * 255) / (pixelCount - 1)));
    }

    return equalized;
}
#pragma clang diagnostic pop


cv::Mat ImageProcessing::match(const cv::Mat &img, const cv::Mat &ref) {
    auto hist = ImageProcessing::hist(img);
    auto cdf = ImageProcessing::cdf(hist);
    auto cdfNorm = ImageProcessing::cdfNorm(cdf);

    auto refHist = ImageProcessing::hist(ref);
    auto refCdf = ImageProcessing::cdf(refHist);
    auto refCdfNorm = ImageProcessing::cdfNorm(refCdf);

    auto res = img.clone();

    std::vector<uchar> colors(256);
    for (auto i = 0; i < cdfNorm.size(); ++i) {
        auto delta = 1e5;
        auto nearest = 0;

        for (auto j = 0; j < refCdfNorm.size(); ++j) {
            auto localDelta = std::fabs(cdfNorm[i] - refCdfNorm[j]);
            if (localDelta < delta) {
                delta = localDelta;
                nearest = j;
            }
        }

        colors[i] = nearest;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
    for (auto el = res.begin<uchar>(); el != res.end<uchar>(); ++el) {
        *el = colors[*el];
    }
#pragma clang diagnostic pop

    return res;
}
