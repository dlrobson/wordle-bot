#include <solver/solver.h>

Wordle::WordList Solver::solve(Wordle::Word wordle_word) {
    wordle_.reset(original_word_list_, wordle_word);
    Wordle::WordList solution_path;
    Wordle::Word guess = "";
    while (guess != wordle_word) {
        guess = next_word();
        solution_path.emplace_back(guess);

        if (guess == wordle_word) {
            return solution_path;
        }

        wordle_.update_list(guess);
    }

    return solution_path;
}
