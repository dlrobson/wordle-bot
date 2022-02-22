#include <solver/solver_benchmark.h>

static constexpr auto MAX_COUNT_SIZE = 12;

SolverBenchmark::SolverBenchmark(const std::string& word_list_path,
                                 const std::string& allowed_word_list_path) {
    word_list_ = read_list(word_list_path);
    allowed_word_list_ = read_list(allowed_word_list_path);
    solver_ = WordleSolver();
}

std::vector<size_t> SolverBenchmark::operator()() {
    std::vector<size_t> guess_frequency(MAX_COUNT_SIZE, 0);
    for (const auto& word : word_list_) {
        solver_.set_word_list(allowed_word_list_);
        const auto sol = solver_.positional_solve(word);
        guess_frequency[sol.size() - 1]++;
    }
    return guess_frequency;
}
