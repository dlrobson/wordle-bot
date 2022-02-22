#pragma once

#include <solver/solver.h>

#include <string>
#include <vector>

class FrequencySolver : public Solver {
   public:
    FrequencySolver(const std::string& word_list_path);
    FrequencySolver(Wordle::WordList word_list);
    ~FrequencySolver() = default;

    Wordle::WordList solve(Wordle::Word wordle_word) override;

   private:
    Wordle::Word next_word() override;

    Wordle::WordList original_word_list_;

    Wordle wordle_;
};