#pragma once

#include <string>
#include <vector>

static constexpr uint8_t WORD_LENGTH = 5;
static constexpr uint8_t NUM_LETTERS = 26;

class WordleGuesser {
   public:
    using Word = std::string;
    using Letters = std::string;

    WordleGuesser(std::string word_list_path);

    std::vector<Word> solve(Word wordle_word);

    // const std::vector<Word>& word_list() const;

   private:
    struct Statistics {
        std::vector<uint16_t> letter_count{NUM_LETTERS, 0};

        std::vector<float> letter_freq{NUM_LETTERS};

        std::vector<std::vector<uint16_t>> location_letter_count{
            WORD_LENGTH, std::vector<uint16_t>(NUM_LETTERS, 0)};

        std::vector<std::vector<float>> location_letter_freq{
            WORD_LENGTH, std::vector<float>(NUM_LETTERS)};
    };
    std::vector<Word> word_list_;

    std::vector<Word> word_guesses_;

    Letters invalid_letters_;

    Letters found_letters_;

    std::vector<Letters> valid_found_letter_locations;

    Statistics list_stats_;

    Word next_word();

    void update_list();
};
