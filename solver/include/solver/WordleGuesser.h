#pragma once

#include <cstdint>
#include <string>
#include <vector>

static constexpr uint8_t WORD_LENGTH = 5;
static constexpr uint8_t NUM_LETTERS = 26;

class WordleGuesser {
   public:
    using Word = std::string;
    using Letters = std::string;

    WordleGuesser(std::string word_list_path);

    Word next_word();

    std::vector<Word> solve(Word wordle_word);

   private:
    struct Statistics {
        std::vector<uint32_t> letter_count;

        std::vector<double> letter_freq;

        std::vector<std::vector<uint32_t>> location_letter_count;

        std::vector<std::vector<double>> location_letter_freq;
    };
    std::vector<Word> word_list_;

    std::vector<Word> word_guesses_;

    std::vector<Letters> valid_letters_;

    Letters required_letters_ = "";

    Statistics list_stats_;

    void update_list(const WordleGuesser::Word& wordle_word,
                     const WordleGuesser::Word& guess);

    size_t letter_to_index(const char& c);
};
