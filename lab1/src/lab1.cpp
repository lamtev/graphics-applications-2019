//
// Created by anton on 12.11.2019.
//

#include <vector>
#include "FigReader.h"
#include "Stretching.h"
#include "Equalization.h"

int main(int argc, char **argv) {
    std::vector<std::string> args;
    args.reserve(argc - 1);
    for (int i = 0; i < argc - 1; ++i) {
        if (strcmp(argv[i + 1], "//") == 0) {
            break;
        }

        args.emplace_back(argv[i + 1]);
    }

    auto figs = FigReader::readFigs(args);

    lab1::Stretching::doExp(figs);
    lab1::Equalization::doExp(figs);

    return 0;
}
