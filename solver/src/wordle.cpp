#include <limits.h>
#include <solver/wordle.h>
#include <solver/wordle_utils.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

Wordle::Wordle(Wordle::WordList word_list, Wordle::Word wordle_word)
    : wordle_word_{wordle_word},
      word_list_{std::move(word_list)},
      valid_letters_{std::vector<std::string>(WORD_LENGTH, ALPHABET)} {}

void Wordle::reset(Wordle::WordList word_list, Wordle::Word wordle_word) {
    wordle_word_ = wordle_word;
    word_list_ = std::move(word_list);
    valid_letters_ = std::vector<std::string>(WORD_LENGTH, ALPHABET);
    required_letters_ = "";
    max_duplicates_.clear();
}

const Wordle::WordList& Wordle::word_list() const { return word_list_; };

bool Wordle::is_guess_valid(const Wordle::Word& guess) {
    auto is_valid = true;
    for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH; letter_pos_i++) {
        const auto& c = guess[letter_pos_i];

        // This letter cannot be in this position. Invalid word
        if (std::count(valid_letters_[letter_pos_i].begin(),
                       valid_letters_[letter_pos_i].end(), c) == 0) {
            is_valid = false;
            break;
        }
    }

    if (!is_valid) {
        return false;
    }

    // Verify that each letter in the required letters list is contained
    // in this word Handle dups
    for (const auto& c : required_letters_) {
        // If there is less letter than required, this is an invalid
        // word
        const auto req_letter_count =
            std::count(required_letters_.begin(), required_letters_.end(), c);
        const auto word_letter_count =
            std::count(guess.begin(), guess.end(), c);

        // The max_duplicates map should be checked to ensure we don't
        // have any word containing more letters than it should.
        auto max_letter_count = INT_MAX;
        if (max_duplicates_.count(c)) {
            max_letter_count = max_duplicates_.at(c);
        }

        if (word_letter_count < req_letter_count ||
            word_letter_count > max_letter_count) {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

Wordle::WordList Wordle::update_list(const std::string& guess) {
    // If we guessed there are more of a letter than present in a word, we
    // need to store this additional information
    std::vector<std::string> new_word_list;

    // Update the known letters vector so that we know what letters are in
    // the final word
    for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH; letter_pos_i++) {
        const auto& c = guess[letter_pos_i];

        // If our guess has more than one of a letter and our guess does
        // too, make sure there are that many in the required_letters vec
        const auto letter_count =
            std::count(wordle_word_.begin(), wordle_word_.end(), c);

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
            max_duplicates_.insert_or_assign(c, correct_count);
        }
    }

    // Update the valid letters for each letter position.
    for (auto letter_pos_i = 0; letter_pos_i < WORD_LENGTH; letter_pos_i++) {
        const auto& c = guess[letter_pos_i];
        // If the letter is in the correct location, it must be here.
        // Replace the list with the single letter
        if (c == wordle_word_[letter_pos_i]) {
            valid_letters_[letter_pos_i] = c;
            continue;
        }

        // If the letter is not in the word, remove the letter from every
        // list. It can't be within this word
        const auto letter_count =
            std::count(wordle_word_.begin(), wordle_word_.end(), c);
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
    for (const auto& word : word_list_) {
        auto is_valid = is_guess_valid(word);
        if (is_valid) {
            new_word_list.emplace_back(std::move(word));
        }
    }
    word_list_ = new_word_list;
    return new_word_list;
}
