#include <limits.h>
#include <math.h>
#include <solver/wordle_solver.h>

#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>

static constexpr auto A_OFFSET = 97;
static constexpr auto ALPHABET = "abcdefghijklmnopqrstuvwxyz";

WordleSolver::WordleSolver(const std::string& word_list_path)
    : word_list_{read_list(word_list_path)},
      valid_letters_{std::vector<std::string>(WORD_LENGTH, ALPHABET)} {}

WordleSolver::WordleSolver(std::vector<std::string> word_list)
    : word_list_{std::move(word_list)},
      valid_letters_{std::vector<std::string>(WORD_LENGTH, ALPHABET)} {}

void WordleSolver::set_word_list(std::vector<std::string> word_list) {
    word_list_ = std::move(word_list);
    valid_letters_ = std::vector<std::string>(WORD_LENGTH, ALPHABET);
    word_guesses_ = std::vector<std::string>();
    required_letters_ = "";
}

void WordleSolver::reset_statistics() {
    letter_count_ = std::vector<uint32_t>(NUM_LETTERS, 0);
    letter_freq_ = std::vector<double>(NUM_LETTERS, 0);
    location_letter_count_ = std::vector<std::vector<uint32_t>>(
        WORD_LENGTH, std::vector<uint32_t>(NUM_LETTERS, 0));
    location_letter_freq_ = std::vector<std::vector<double>>(
        WORD_LENGTH, std::vector<double>(NUM_LETTERS, 0));
}
void WordleSolver::generate_statistics() {
    reset_statistics();
    // Generate the count statistics
    for (const auto& word : word_list_) {
        for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH;
             letter_pos_i++) {
            const auto& letter = word[letter_pos_i];
            const auto letter_index = letter_to_index(letter);
            letter_count_[letter_index]++;
            location_letter_count_[letter_pos_i][letter_index]++;
        }
    }

    // Generate the frequency statistics
    for (auto letter_i = 0; letter_i < NUM_LETTERS; letter_i++) {
        const auto& letter_count = letter_count_[letter_i];
        letter_freq_[letter_i] =
            letter_count / static_cast<float>(word_list_.size() * WORD_LENGTH);
    }

    // Generate the positional frequency statistics
    for (auto letter_i = 0; letter_i < NUM_LETTERS; letter_i++) {
        for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH;
             letter_pos_i++) {
            const auto& letter_count =
                location_letter_count_[letter_pos_i][letter_i];
            location_letter_freq_[letter_pos_i][letter_i] =
                letter_count / static_cast<float>(word_list_.size());
        }
    }
}

std::vector<std::string> WordleSolver::positional_solve(
    std::string wordle_word) {
    std::string guess = "";

    while (guess != wordle_word) {
        guess = positional_next_word();
        word_guesses_.emplace_back(guess);

        if (guess == wordle_word) {
            return word_guesses_;
        }

        update_list(wordle_word, guess);
    }

    return word_guesses_;
}

std::vector<std::string> WordleSolver::frequency_solve(
    std::string wordle_word) {
    std::string guess = "";

    while (guess != wordle_word) {
        guess = frequency_next_word();
        word_guesses_.emplace_back(guess);

        if (guess == wordle_word) {
            return word_guesses_;
        }

        update_list(wordle_word, guess);
    }

    return word_guesses_;
}

std::string WordleSolver::positional_next_word() {
    generate_statistics();

    double best_score = 0.0;
    std::string best_word;
    // Iterate through each word, and assign a score. Keep track of the best
    // score
    for (const auto& word : word_list_) {
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
                location_letter_freq_[letter_i][letter_val] *
                pow(letter_freq_[letter_val], occurences);
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

std::string WordleSolver::frequency_next_word() {
    generate_statistics();

    double best_score = 0.0;
    std::string best_word;
    // Iterate through each word, and assign a score. Keep track of the best
    // score
    for (const auto& word : word_list_) {
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
            const auto letter_score = pow(letter_freq_[letter_val], occurences);
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

void WordleSolver::update_list(const std::string& wordle_word,
                               const std::string& guess) {
    // If we guessed there are more of a letter than present in a word, we
    // need to store this additional information
    std::unordered_map<char, int> max_duplicates;

    // Update the known letters vector so that we know what letters are in
    // the final word
    for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH; letter_pos_i++) {
        const auto& c = guess[letter_pos_i];

        // If our guess has more than one of a letter and our guess does
        // too, make sure there are that many in the required_letters vec
        const auto letter_count =
            std::count(wordle_word.begin(), wordle_word.end(), c);

        // We know there is no updating to do if the letter isn't in the
        // word
        if (letter_count == 0) {
            continue;
        }

        const auto guess_letter_count =
            std::count(guess.begin(), guess.end(), c);

        const auto correct_count = std::min(letter_count, guess_letter_count);

        // This adds letters to the valid_letters list until we have the
        // correct number
        while (std::count(required_letters_.begin(), required_letters_.end(),
                          c) < correct_count) {
            required_letters_.push_back(c);
        }
        // We guessed there were more of a character than actually present.
        // Store this for later filtering
        if (guess_letter_count > correct_count) {
            max_duplicates.insert_or_assign(c, correct_count);
        }
    }

    // Update the valid letters for each letter position.
    for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH; letter_pos_i++) {
        const auto& c = guess[letter_pos_i];
        // If the letter is in the correct location, it must be here.
        // Replace the list with the single letter
        if (c == wordle_word[letter_pos_i]) {
            valid_letters_[letter_pos_i] = c;
            continue;
        }

        // If the letter is not in the word, remove the letter from every
        // list. It can't be within this word
        const auto letter_count =
            std::count(wordle_word.begin(), wordle_word.end(), c);
        if (letter_count == 0) {
            for (auto i = 0; i < WORD_LENGTH; i++) {
                valid_letters_[i].erase(remove(valid_letters_[i].begin(),
                                               valid_letters_[i].end(), c),
                                        valid_letters_[i].end());
            }
            continue;
        }

        // At this point, the letter is within the word but in the incorrect
        // location. Remove the letter as a possibility for this location
        valid_letters_[letter_pos_i].erase(
            remove(valid_letters_[letter_pos_i].begin(),
                   valid_letters_[letter_pos_i].end(), c),
            valid_letters_[letter_pos_i].end());
    }

    // Now that we know the new word requirements, we will filter through
    // each word, checking if it's a valid fit.
    std::vector<std::string> new_word_list;
    for (const auto& word : word_list_) {
        auto is_valid = true;
        for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH;
             letter_pos_i++) {
            const auto& c = word[letter_pos_i];

            // This letter cannot be in this position. Invalid word
            if (std::count(valid_letters_[letter_pos_i].begin(),
                           valid_letters_[letter_pos_i].end(), c) == 0) {
                is_valid = false;
                break;
            }
        }

        if (!is_valid) {
            continue;
        }

        // Verify that each letter in the required letters list is contained
        // in this word Handle dups
        for (const auto& c : required_letters_) {
            // If there is less letter than required, this is an invalid
            // word
            const auto req_letter_count = std::count(
                required_letters_.begin(), required_letters_.end(), c);
            const auto word_letter_count =
                std::count(word.begin(), word.end(), c);

            // The max_duplicates map should be checked to ensure we don't
            // have any word containing more letters than it should.
            auto max_letter_count = INT_MAX;
            if (max_duplicates.count(c)) {
                max_letter_count = max_duplicates.at(c);
            }

            if (word_letter_count < req_letter_count ||
                word_letter_count > max_letter_count) {
                is_valid = false;
                break;
            }
        }
        if (is_valid) {
            new_word_list.emplace_back(std::move(word));
        }
    }
    word_list_ = new_word_list;
}

size_t WordleSolver::letter_to_index(const char& c) {
    return size_t(c) - A_OFFSET;
}

std::vector<std::string> read_list(const std::string& path) {
    std::vector<std::string> words;
    std::ifstream file(path);
    std::string wordle_word;
    while (std::getline(file, wordle_word)) {
        words.emplace_back(wordle_word);
    }
    return words;
}
