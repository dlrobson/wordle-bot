#pragma once

#include <vector>

struct WordStatistics {
    std::vector<uint32_t> letter_count;

    std::vector<double> letter_freq;

    std::vector<std::vector<uint32_t>> location_letter_count;

    std::vector<std::vector<double>> location_letter_freq;
};