#pragma once

#include <solver/wordle.h>

#include <string>
#include <vector>

class Solver {
   public:
    virtual Wordle::WordList solve(Wordle::Word wordle_word) = 0;

   private:
    virtual Wordle::Word next_word() = 0;
};