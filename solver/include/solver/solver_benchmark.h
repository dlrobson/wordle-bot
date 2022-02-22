#pragma once

#include <solver/wordle_solver.h>

class SolverBenchmark {
   public:
    SolverBenchmark(const std::string& word_list_path,
                    const std::string& allowed_word_list_path);

    std::vector<size_t> operator()(size_t mode);

   private:
    WordleSolver solver_;

    std::vector<std::string> word_list_;

    std::vector<std::string> allowed_word_list_;
};
