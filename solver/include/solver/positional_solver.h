#pragma once

#include <solver/solver.h>

#include <string>
#include <vector>

class PositionalSolver : public Solver {
   public:
    PositionalSolver(const std::string& word_list_path);
    PositionalSolver(Wordle::WordList word_list);
    ~PositionalSolver() = default;

    Wordle::WordList solve(Wordle::Word wordle_word) override;

   private:
    Wordle::Word next_word() override;

    Wordle::WordList original_word_list_;

    Wordle wordle_;
};