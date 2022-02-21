#include <solver/WordleGuesser.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {
    WordleGuesser solver(
        "/home/dlrobson/dev/wordle-bot/3rd-party/wordlist/"
        "wordle-answers-alphabetical.txt");

    std::string word = "slate";
    if (argc == 2) {
        word = argv[1];
    }

    if (word == "-b") {
        // RUN BENCHMARK
        std::cout << "Average Guesses: " << std::endl;
        return EXIT_SUCCESS;
    }

    if (word.size() != 5) {
        std::cout << "Incorrect word length. Word must be 5 long." << std::endl;
        return EXIT_FAILURE;
    }

    const auto solution = solver.solve(word);
    for (const auto& w : solution) {
        std::cout << w << std::endl;
    }

    return EXIT_SUCCESS;
}
