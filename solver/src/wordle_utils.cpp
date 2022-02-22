#include <solver/wordle_utils.h>

#include <fstream>

WordStatistics generate_statistics(std::vector<Wordle::Word> word_list) {
    WordStatistics stats;

    stats.letter_count = std::vector<uint32_t>(NUM_LETTERS, 0);
    stats.letter_freq = std::vector<double>(NUM_LETTERS, 0);
    stats.location_letter_count = std::vector<std::vector<uint32_t>>(
        WORD_LENGTH, std::vector<uint32_t>(NUM_LETTERS, 0));
    stats.location_letter_freq = std::vector<std::vector<double>>(
        WORD_LENGTH, std::vector<double>(NUM_LETTERS, 0));

    // Generate the count statistics
    for (const auto& word : word_list) {
        for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH;
             letter_pos_i++) {
            const auto& letter = word[letter_pos_i];
            const auto letter_index = letter_to_index(letter);
            stats.letter_count[letter_index]++;
            stats.location_letter_count[letter_pos_i][letter_index]++;
        }
    }

    // Generate the frequency statistics
    for (auto letter_i = 0; letter_i < NUM_LETTERS; letter_i++) {
        const auto& letter_count = stats.letter_count[letter_i];
        stats.letter_freq[letter_i] =
            letter_count / static_cast<float>(word_list.size() * WORD_LENGTH);
    }

    // Generate the positional frequency statistics
    for (auto letter_i = 0; letter_i < NUM_LETTERS; letter_i++) {
        for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH;
             letter_pos_i++) {
            const auto& letter_count =
                stats.location_letter_count[letter_pos_i][letter_i];
            stats.location_letter_freq[letter_pos_i][letter_i] =
                letter_count / static_cast<float>(word_list.size());
        }
    }
    return stats;
}

size_t letter_to_index(const char& c) { return size_t(c) - A_OFFSET; }

std::vector<std::string> read_list(const std::string& path) {
    std::vector<std::string> words;
    std::ifstream file(path);
    std::string wordle_word;
    while (std::getline(file, wordle_word)) {
        words.emplace_back(wordle_word);
    }
    return words;
}
