#include <solver/WordleGuesser.h>

#include <fstream>

static constexpr auto A_OFFSET = 97;

WordleGuesser::WordleGuesser(std::string word_list_path) {
    std::ifstream file(word_list_path);
    std::string wordle_word;
    while (std::getline(file, wordle_word)) {
        word_list_.emplace_back(wordle_word);
    }
}

std::vector<WordleGuesser::Word> WordleGuesser::solve(
    WordleGuesser::Word wordle_word) {
    return word_guesses_;
}

WordleGuesser::Word WordleGuesser::next_word() {
    // Generate the count statistics
    for (const auto& word : word_list_) {
        for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH;
             letter_pos_i++) {
            const auto& letter = word[letter_pos_i];
            const auto letter_index = letter - A_OFFSET;
            list_stats_.letter_count[letter_index]++;
            list_stats_.location_letter_count[letter_pos_i][letter_index]++;
        }
    }

    // Generate the frequency statistics
    for (auto letter_i = 0; letter_i < NUM_LETTERS; letter_i++) {
        const auto& letter_count = list_stats_.letter_count[letter_i];
        list_stats_.letter_freq[letter_i] =
            letter_count / static_cast<float>(word_list_.size() * WORD_LENGTH);
    }
    // Generate the positional frequency statistics
    for (auto letter_i = 0; letter_i < NUM_LETTERS; letter_i++) {
        for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH;
             letter_pos_i++) {
            const auto& letter_count =
                list_stats_.location_letter_count[letter_pos_i][letter_i];
            list_stats_.letter_freq[letter_i] =
                letter_count / static_cast<float>(word_list_.size());
        }
    }
    return "";
}
