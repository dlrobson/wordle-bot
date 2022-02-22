#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Wordle {
   public:
    using Word = std::string;
    using WordList = std::vector<std::string>;

    Wordle() = default;
    Wordle(WordList word_list, Word wordle_word);
    ~Wordle() = default;

    void reset(WordList word_list, Word wordle_word);

    void word_list(WordList word_list);

    const WordList& word_list() const;

    bool is_guess_valid(const Word& guess);

    WordList update_list(const Word& guess);

   private:
    Word wordle_word_;

    WordList word_list_;

    std::vector<std::string> valid_letters_;

    std::string required_letters_ = "";

    std::unordered_map<char, int> max_duplicates_;
};
