#pragma once

#include <solver/solver.h>
#include <solver/wordle.h>

#include <string>

class PositionalSolver : public Solver {
   public:
    PositionalSolver(const std::string& word_list_path);
    PositionalSolver(Wordle::WordList word_list);
    ~PositionalSolver() = default;

   private:
    Wordle::Word next_word() override;
};