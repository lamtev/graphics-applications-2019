//
// Created by anton on 12.11.2019.
//

#include <iostream>
#include <vector>
//#include "matplotlibcpp.h"
#include <opencv4/opencv2/opencv.hpp>
#include "hist.h"
#include "FigReader.h"
#include "stretching.h"
#include "equalization.h"

int main(int argc, char **argv) {
    std::vector<std::string> paths;
    paths.reserve(argc - 1);
    for (int i = 0; i < argc - 1; ++i) {
        paths.emplace_back(argv[i + 1]);
    }

    auto figs = FigReader::readFigs(paths);

//    doStretchingExp(figs);
    doEqualizationExp(figs);
//
//    std::cout << "Hello, World!" << std::endl;
//    return 0;

//    if (argc != 2) {
//        printf("usage: DisplayImage.out <Image_Path>\n");
//        return -1;
//    }
//    auto image = cv::imread(argv[1], cv::IMREAD_COLOR);
//    if (!image.data) {
//        printf("No image data \n");
//        return -1;
//    }
//    cv::Mat gray;
//    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
//    gray.convertTo(gray, -1, 0.2F, 0.F);
//
//    auto hist = ::hist(gray);
//
//    plt::plot(hist);
//    plt::show(false);
//
//    cv::resize(image, image, cv::Size(), 0.25F, 0.25F);
//    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
//    cv::imshow("Original", image);
//
//    cv::resize(gray, gray, cv::Size(), 0.25F, 0.25F);
//    cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
//    cv::imshow("Gray", gray);
//    cv::waitKey(0);

    return 0;
}
