#include <math.h>
#include <solver/frequency_solver.h>
#include <solver/wordle_utils.h>

#include <algorithm>
#include <string>
#include <vector>

FrequencySolver::FrequencySolver(const std::string& word_list_path)
    : original_word_list_{read_list(word_list_path)},
      wordle_{Wordle(original_word_list_, Wordle::Word())} {};

FrequencySolver::FrequencySolver(Wordle::WordList word_list)
    : original_word_list_{std::move(word_list)},
      wordle_{Wordle(original_word_list_, Wordle::Word())} {};

std::vector<Wordle::Word> FrequencySolver::solve(Wordle::Word wordle_word) {
    wordle_.reset(original_word_list_, wordle_word);
    Wordle::WordList solution_path;
    Wordle::Word guess = "";
    while (guess != wordle_word) {
        guess = next_word();
        solution_path.emplace_back(guess);

        if (guess == wordle_word) {
            return solution_path;
        }

        wordle_.update_list(guess);
    }

    return solution_path;
}

Wordle::Word FrequencySolver::next_word() {
    const auto& word_list = wordle_.word_list();

    const auto stats = generate_statistics(word_list);

    double best_score = 0.0;
    std::string best_word;
    // Iterate through each word, and assign a score. Keep track of the best
    // score
    for (const auto& word : word_list) {
        double score = 0;
        for (auto letter_i = 0; letter_i < WORD_LENGTH; letter_i++) {
            const auto& letter = word[letter_i];
            // If this letter has already been read, then count how many
            // times it's been accounted for already
            auto occurences = 1;
            if (std::count(word.begin(), word.end(), letter) != 1) {
                for (auto letter_j = 0; letter_j < letter_i; letter_j++) {
                    if (word[letter_j] == letter) {
                        occurences++;
                    }
                }
            }

            // Calculate the score of the word. The score is determined by
            // the sum of the letter frequency of the letter. This is
            // determined by multiplying the probability of the letter, by
            // the probability of the letter being in that position.

            // Duplicate letters are less frequent. They will be calculated
            // as the P(letter)^(count)
            // TODO(): Replace this independent probability assumption for
            // the duplicate letters
            const auto letter_val = letter_to_index(letter);
            const auto letter_score =
                pow(stats.letter_freq[letter_val], occurences);
            score += letter_score;
        }

        // This word is better than our current best. Update it
        if (score > best_score) {
            best_score = score;
            best_word = word;
        }
    }
    return best_word;
}
