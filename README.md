# WIP
Still lots to do. Need to:
- https://jameshfisher.com/2018/11/25/google-ngram-api/
- https://github.com/econpy/google-ngrams/blob/master/getngrams.py
- See if it's alright that I'm using the wordle list
- Find the frequency of each 5 letter word. Probably best to save this to file
- Determine method to calculate the optimal word
- Create data structure to hold the current guesses, and determine and return the optimal word
- Create a test file that iterates through each word in the word list, and returns the average number of guesses
- Add input/output to main file
- Output the guesses. Add coloured letters if possible?

# Features
- Only plays in hard mode! 

# Steps to Install
Set up `conan`:
```bash
conan profile new --detect default
conan profile update settings.compiler.libcxx=libstdc++11 default
mkdir build && cd build
```

For your first installation, you will also need to run this while in the `build` directory:
```bash
conan install ..
```

Also run that command when you add a package to conan. You can add a conan file to the `conanfile.txt` file. Check for conan packages at the [conan center](https://conan.io/center/).

You should be able to then run the solver using
```bash
bin/build/solve_wordle word
```

It will output the words it guessed to reach your input word!
