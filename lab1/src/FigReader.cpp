//
// Created by anton on 20.12.2019.
//

#include "FigReader.h"
#include "Fig.h"
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>

std::vector<Fig> FigReader::readFigs(const std::vector<std::string> &args) {
    std::vector<Fig> figs;
    figs.reserve(args.size() / 3);

    for (auto i = 0; i < args.size(); i += 3) {
        std::string path(args[i]);
        auto img = cv::imread(path, cv::IMREAD_GRAYSCALE);
        if (!img.data) {
            continue;
        }

        auto lastSlashIdx = path.find_last_of('/');

        auto lastFileNameCharIdx = path.find_last_of(".jpg");
        if (lastFileNameCharIdx == -1) {
            lastFileNameCharIdx = path.find_last_of(".png");
        }
        lastFileNameCharIdx -= 1;

        figs.emplace_back(
                path.substr(lastSlashIdx + 1, lastFileNameCharIdx - lastSlashIdx - 3),
                img,
                std::strtol(args[i + 1].c_str(), nullptr, 10),
                std::strtol(args[i + 2].c_str(), nullptr, 10)
        );
    }

    return figs;
}
