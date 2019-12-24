//
// Created by anton on 20.12.2019.
//

#pragma once

#include <vector>
#include <string>

class Fig;

class FigReader {
public:
    static std::vector<Fig> readFigs(const std::vector<std::string> &args);
};
