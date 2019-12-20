//
// Created by anton on 20.12.2019.
//

#include "FigReader.h"
#include <algorithm>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>

std::vector<Fig> FigReader::readFigs(const std::vector<std::string> &paths) {
    std::vector<Fig> figs;
    figs.reserve(paths.size());

    std::for_each(paths.cbegin(), paths.cend(), [&figs](const std::string &path) {
        auto img = cv::imread(path, cv::IMREAD_COLOR);
        if (!img.data) {
            return;
        }

        auto lastSlashIdx = path.find_last_of('/');

        auto lastFileNameCharIdx = path.find_last_of(".jpg");
        if (lastFileNameCharIdx == -1) {
            lastFileNameCharIdx = path.find_last_of(".png");
        }
        lastFileNameCharIdx -= 1;

        figs.emplace_back(path.substr(lastSlashIdx + 1, lastFileNameCharIdx - lastSlashIdx - 3), img);
    });

    return figs;
}
