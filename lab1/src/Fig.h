//
// Created by anton on 20.12.2019.
//

#pragma once

#include <string>
#include <opencv4/opencv2/core/mat.hpp>

class Fig {
private:
    std::string _name;
    cv::Mat _img;
    int _lowDropBound;
    int _highDropBound;

public:
    Fig(std::string name, cv::Mat img, int lowDropBound, int highDropBound) noexcept :
            _name(std::move(name)),
            _img(std::move(img)),
            _lowDropBound(lowDropBound),
            _highDropBound(highDropBound) {}

    [[nodiscard]] const std::string &name() const noexcept {
        return _name;
    }

    [[nodiscard]] const cv::Mat &img() const noexcept {
        return _img;
    }

    [[nodiscard]] int lowDropBound() const noexcept {
        return _lowDropBound;
    }

    [[nodiscard]] int highDropBound() const noexcept {
        return _highDropBound;
    }
};
