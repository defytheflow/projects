# This little script helps you learn new words!

# First you create a file with following structure:
# At the top of the file write a declaration like the following:

# english word [separ] definition [separ] hint

# You can use any punctuation separator you want as long as it stays
# the same throughout your whole file.

# This will let the program now how to differ english words from
# its' definitions and hints.

# Note that program requires a hint, if you don't need it just type 0 instead of it.

# Then main loop starts and asks you for a word that corresponds to a given
# definition, it will run until you get all words right.
# You can type h or hint fory a hint that you left for yourself in the file.
# also type q or quit to prematurely stop the program.

# Notice that all functions start with a forward _ , that indicates
# those functions are only for an internal use in this script(program).
# They are private. Also if you were to import this file as a module to your
# program or repl prompt, all funcs starting with _ wouldn't load.

import sys
import string
import random


def main():
    try:
        file = sys.argv[1]
    except IndexError:
        quit("I need a file with your words as an argument to work.")
    words = _load_words(file)
    sep = _define_sep(words)
    engs, defns, hints = _split_words(words, sep)
    assert len(engs) == len(defns) == len(hints), "Words haven't been splitted equally."
    _learn(engs, defns, hints)


def _load_words(file) -> list:
    """ Loads words from a given file and shuffles them. """
    try:
        with open(file, "r") as file:
            lines = [line.lower().rstrip() for line in file.readlines()]
    except FileNotFoundError as er:
        print(er)
        quit()
    else:
        return lines


def _define_sep(words: list) -> str:
    """ Returns whatever separator is being used to split the words. """
    first_line = words.pop(0)
    for sep in string.punctuation:
         if first_line.count(sep) == 2:

             for line in words:
                 if not line.count(sep) == 2:
                     quit("Separator declaration in your file seems "
                          "to be incorrect.")
                 else:
                     return sep

    quit("Add 'engword [sep] defin [sep] hint' "
         "at the begginning of your words file.")


def _split_words(words: list, sep: str) -> tuple:
    """
        Splits given words into englishwords, definitions and hints.
        Returns them as a tuple of length 3.
    """
    random.shuffle(words)

    engs = []
    defns = []  # stands for definitions
    hints = []

    # I call it a line here because it's not only a word we iterate
    # over but also it's defenition and hint.
    for line in words:
        sep1, sep2 = _find_seps(line, sep)
        eng = line[:sep1].strip()
        defn = line[sep1 + 1:sep2].strip()
        hint = line[sep2 + 1:].strip()

        engs.append(eng)
        defns.append(defn)
        hints.append(hint)
    return engs, defns, hints


def _find_seps(line: str, sep: str):
    """ Returns indexes of separators used in the line. """
    sep_inds = []
    for ind, char in enumerate(line):
        try:
            if char == sep and line[ind-1] == " " and line[ind+1] == " ":
                    sep_inds.append(ind)
        except IndexError:
            print("Apparently, you are missing either a definition or a hint somewhere "
                  "in your file.\nNote: If you don't need any hints just type 0 after "
                  "word's definition instead.")
            quit()
    assert len(sep_inds) == 2, "Something is wrong with the separators in your file."
    return tuple(sep_inds)


def _learn(engs: list, defns: list, hints: list):
    """ Main function that helps learn new words. """
    correct = []
    mistakes = 0

    def summarize():
        """ Returns stats. """
        print("\nYour stats:")
        print(f"Correct: {len(correct)}")
        print(f"Mistakes: {mistakes}")
        if not mistakes:
            print("You did not make a single mistake. Great job!")
        else:
            print("Not bad! Just try one more time!")
        quit("\nBye.")

    # The Main loop that runs until user has got all words correct
    # or stopped on intention.
    while len(correct) != len(engs):
        for eng, defn, hint in zip(engs, defns, hints):
            if (eng, defn) in correct:
                continue
            else:
                if _prompt_user(eng, defn, hint):
                    correct.append((eng, defn))
                    print(f"Correct! ({len(correct)}/{len(engs)})")
                else:
                    mistakes += 1
                    print(f"Mistake! ({mistakes})")
                    print(f"Correct word is {eng}.")

    return summarize()


def _prompt_user(eng: str, defn: str, hint: str):
    """
        Prompts the user for an english word corresponding to
        it's definition, can display hint if typed "h" or "hint"
        or if typed "q" or "quit" or "stop" stops the program.
    """
    while True:
        user_eng = input("\n" + defn.capitalize() + " - ").lower().strip()
        if user_eng in ("q", "quit", "stop"):
            quit("Bye")
        elif user_eng in ("h", "hint"):
            print(f"Hint: {hint}")
        else:
            if user_eng == eng:
                return True
            else:
                return False


# Defining your own Exceptions can be quite useful as it can help
# a user understand what went wrong.
class _NotFoundSeparatorError(Exception):
    """ Raised if the program can't identify the separator used. """


if __name__ == "__main__":
    print()
    main()






