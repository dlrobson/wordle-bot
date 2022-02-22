#include <solver/frequency_solver.h>
#include <solver/positional_solver.h>
#include <solver/solver_benchmark.h>
#include <solver/wordle_utils.h>

#include <memory>

#include "solver/solver.h"

static constexpr auto MAX_COUNT_SIZE = 12;

SolverBenchmark::SolverBenchmark(const std::string& word_list_path,
                                 const std::string& allowed_word_list_path) {
    word_list_ = read_list(word_list_path);
    allowed_word_list_ = read_list(allowed_word_list_path);
}

std::vector<size_t> SolverBenchmark::operator()(size_t mode) {
    set_solver(mode);
    std::vector<size_t> guess_frequency(MAX_COUNT_SIZE, 0);
    for (const auto& word : word_list_) {
        const auto sol = solver_->solve(word);
        guess_frequency[sol.size() - 1]++;
    }
    return guess_frequency;
}

void SolverBenchmark::set_solver(size_t mode) {
    switch (mode) {
        case 0:
            solver_ = std::make_unique<PositionalSolver>(word_list_);
            break;
        case 1:
            solver_ = std::make_unique<FrequencySolver>(word_list_);
            break;
        case 2:
            break;
    }
}