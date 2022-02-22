#pragma once

#include <solver/solver.h>
#include <solver/statistics.h>

#include <vector>

static constexpr uint8_t WORD_LENGTH = 5;
static constexpr uint8_t NUM_LETTERS = 26;
static constexpr auto A_OFFSET = 97;
static constexpr auto ALPHABET = "abcdefghijklmnopqrstuvwxyz";

WordStatistics generate_statistics(std::vector<Wordle::Word> word_list);

std::vector<std::string> read_list(const std::string& path);

size_t letter_to_index(const char& c);
