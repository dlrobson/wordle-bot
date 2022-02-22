#pragma once

#include <cstdint>
#include <string>
#include <vector>

static constexpr uint8_t WORD_LENGTH = 5;
static constexpr uint8_t NUM_LETTERS = 26;

class WordleSolver {
   public:
    WordleSolver() = default;
    WordleSolver(const std::string& word_list_path);
    WordleSolver(std::vector<std::string> word_list);

    std::string positional_next_word();
    std::string frequency_next_word();

    std::vector<std::string> positional_solve(std::string wordle_word);
    std::vector<std::string> frequency_solve(std::string wordle_word);

    void set_word_list(std::vector<std::string> word_list);

   private:
    std::vector<uint32_t> letter_count_;

    std::vector<double> letter_freq_;

    std::vector<std::vector<uint32_t>> location_letter_count_;

    std::vector<std::vector<double>> location_letter_freq_;

    std::vector<std::string> word_list_;

    std::vector<std::string> word_guesses_;

    std::vector<std::string> valid_letters_;

    std::string required_letters_ = "";

    void update_list(const std::string& wordle_word, const std::string& guess);

    size_t letter_to_index(const char& c);

    void reset_statistics();
    void generate_statistics();
};

std::vector<std::string> read_list(const std::string& path);
