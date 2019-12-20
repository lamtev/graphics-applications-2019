//
// Created by anton on 20.12.2019.
//

#include "hist.h"

std::vector<int> hist(const cv::Mat &fig, int dim) {
    std::vector<int> h(dim, 0);
    for (auto el = fig.begin<uchar>(); el != fig.end<uchar>(); el++) {
        h[*el]++;
    }

    return h;
}
