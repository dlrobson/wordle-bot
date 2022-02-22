#pragma once

#include <solver/solver.h>
#include <solver/wordle.h>

#include <string>

class FrequencySolver : public Solver {
   public:
    FrequencySolver(const std::string& word_list_path);
    FrequencySolver(Wordle::WordList word_list);
    ~FrequencySolver() = default;

   private:
    Wordle::Word next_word() override;
};