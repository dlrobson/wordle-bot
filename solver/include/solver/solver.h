#pragma once

#include <solver/wordle.h>

#include <string>

class Solver {
   protected:
    Wordle wordle_;

    Wordle::WordList original_word_list_;

   public:
    Wordle::WordList solve(Wordle::Word wordle_word);

   private:
    virtual Wordle::Word next_word() = 0;
};