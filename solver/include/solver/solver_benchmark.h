#pragma once

#include <solver/solver.h>

#include <cstddef>
#include <memory>

class SolverBenchmark {
   public:
    SolverBenchmark(const std::string& word_list_path,
                    const std::string& allowed_word_list_path);

    std::vector<size_t> operator()(size_t mode);

   private:
    std::unique_ptr<Solver> solver_ = nullptr;

    void set_solver(size_t mode);

    Wordle::WordList word_list_;

    Wordle::WordList allowed_word_list_;
};
