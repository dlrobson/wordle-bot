#include <solver/solver_benchmark.h>
#include <solver/wordle_solver.h>

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    const auto path =
        "/home/dlrobson/dev/wordle-bot/3rd-party/wordlist/"
        "wordle-answers-alphabetical.txt";

    std::string word = "slate";
    auto mode = 0;
    if (argc <= 3) {
        word = argv[1];
    }
    if (argc == 3) {
        mode = std::stoi(argv[2]);
    }

    if (word == "-b") {
        SolverBenchmark benchmark(path, path);
        std::cout << "Running benchmark..." << std::endl;
        const auto results = benchmark(mode);

        auto total = 0;
        auto weighted_total = 0;

        std::cout << "Bins: ";
        for (size_t i = 0; i < results.size(); i++) {
            total += results[i];
            weighted_total += (i + 1) * results[i];
            std::cout << results[i] << '\t';
        }

        std::cout << std::endl
                  << "Average Guesses: "
                  << weighted_total / static_cast<float>(total) << std::endl;
        return EXIT_SUCCESS;
    }

    if (word.size() != 5) {
        std::cout << "Incorrect word length. Word must be 5 long." << std::endl;
        return EXIT_FAILURE;
    }

    WordleSolver solver(path);
    const auto solution = solver.solve(word, mode);
    for (const auto& w : solution) {
        std::cout << w << std::endl;
    }

    return EXIT_SUCCESS;
}
