#!/usr/bin/python3

'''
    File:     wordcollect.py
    Created:  23.06.2019
    Author:   Artyom Danilov
'''

import random
import readline
import sys
import string

import colorama


COMMANDS = {
    'found':    'f',
    'mistakes': 'm',
    'quit':     'q',
    'words':    'w',
}


class Printer:

    def __init__(self):
        colorama.init()

    def error(self, *args, prefix=False, command=None):
        if command is not None:
            command()
        print(colorama.Fore.RED, 'error: ' if prefix else '', sep='', end='')
        print(*args, colorama.Style.RESET_ALL)

    def info(self, *args, prefix=False, command=None):
        if command is not None:
            command()
        print(colorama.Fore.BLUE, 'info: ' if prefix else '', sep='', end='')
        print(*args, colorama.Style.RESET_ALL)

    def success(self, *args, prefix=False, command=None):
        if command is not None:
            command()
        print(colorama.Fore.GREEN, 'success: ' if prefix else '', sep='', end='')
        print(*args, colorama.Style.RESET_ALL)

    def warning(self, *args, prefix=False, command=None):
        if command is not None:
            command()
        print(colorama.Fore.YELLOW, 'warning: ' if prefix else '', sep='', end='')
        print(*args, colorama.Style.RESET_ALL)

    def primary(self, *args, command=None):
        if command is not None:
            command()
        print(colorama.Fore.MAGENTA, sep='', end='')
        print(*args, colorama.Style.RESET_ALL)



class User:

    def __init__(self):
        self.mistakes = 0
        self.found_words = []

    def inc_mistakes(self):
        self.mistakes += 1


class MistakesLimitExceededError(Exception):
    pass


class Game:

    MISTAKES_LIMIT = 10
    WORDS_LIMIT = 10
    WORD_MIN_LENGTH = 4

    def __init__(self):
        self.user = User()
        self.printer = Printer()

        self.game_word_dict = self.cleared_data_for_game_word('words.txt')
        self.game_word = self.generate_word()
        self.check_word_dict = self.cleared_data_to_check_user_word('words.txt')

        self.print_rules()

    def cleared_data_for_game_word(self, dict: str) -> list:
        """dict for generating game word"""
        with open(dict) as eng_words:
            raw_data = eng_words.readlines()

            def validate(word: str) -> bool:
                if '-' in word or "'" in word or len(word.strip(' ').strip('\n')) <= 15:
                    return False
                return True

            clear_data = [word.strip(' ').rstrip('\n').lower() for word in raw_data if validate(word)]
        return clear_data

    def cleared_data_to_check_user_word(self, dict: str) -> list:
        """dict to check user found word"""
        with open(dict) as eng_words:
            raw_data = eng_words.readlines()

            def validate(word: str) -> bool:
                if '-' in word or "'" in word or len(word.strip(' ').strip('\n')) < 4 \
                        or len(word.strip(' ').strip('\n')) > len(self.game_word):
                    return False
                return True

            clear_data = [word.strip(' ').rstrip('\n').lower() for word in raw_data if validate(word)]
        return clear_data

    def generate_word(self) -> str:
        """generates word from check dict"""
        random_word = random.choice(self.game_word_dict)
        return random_word

    def execute_command(self, command):
        if command == COMMANDS['found']:
            self.printer.info(f'Found words: {self.user.found_words}')
        elif command == COMMANDS['mistakes']:
            self.printer.info(f'Mistakes: {self.user.mistakes}')
        elif command == COMMANDS['quit']:
            sys.exit(0)
        elif command == COMMANDS['words']:
            self.printer.info(f'Words left: {self.WORDS_LIMIT - len(self.user.found_words)}')
        else:
            raise ValueError("Unknown command - '{command}'")

    def is_english(self, word):
        for char in word:
            if char not in string.ascii_lowercase:
                return False
        return True

    def word_can_be_composed(self, word):
        game_word = list(self.game_word)
        for char in word:
            if char in game_word:
                game_word.remove(char)
            else:
                return False
        return True

    def prompt_user(self, msg):
        ''' Main method that does all the validation of user input. '''

        while True:

            if self.user.mistakes == self.MISTAKES_LIMIT:
                raise MistakesLimitExceededError()

            self.printer.primary(f'\n{self.game_word.upper()}\n')
            user_word = input(msg).strip().lower()

            if user_word in COMMANDS.values():
                self.execute_command(user_word)
                continue

            if not user_word:
                self.printer.error('blank input.', prefix=True, command=self.user.inc_mistakes)
                continue

            if not user_word.isalpha():
                self.printer.error('invalid word.', prefix=True, command=self.user.inc_mistakes)
                continue

            if not self.is_english(user_word):
                self.printer.error('invalid english word.', prefix=True, command=self.user.inc_mistakes)
                continue

            if len(user_word) < self.WORD_MIN_LENGTH:
                self.printer.error('short word.', prefix=True, command=self.user.inc_mistakes)
                continue

            if len(user_word) >= len(self.game_word):
                self.printer.error('long word.', prefix=True, command=self.user.inc_mistakes)
                continue

            if user_word not in self.check_word_dict:
                self.printer.error('word does not exist in the game dictionary.',
                                   prefix=True,
                                   command=self.user.inc_mistakes)
                continue

            if user_word in self.user.found_words:
                self.printer.error('word already found.', prefix=True, command=self.user.inc_mistakes)
                continue

            if not self.word_can_be_composed(user_word):
                self.printer.error('cannot compose word.', prefix=True, command=self.user.inc_mistakes)
                continue

            self.printer.success('correct!', command=lambda: self.user.found_words.append(user_word))

    def mainloop(self):
        while True:
            try:
                self.prompt_user('Found word: ')
            except MistakesLimitExceededError:
                self.error('Game over! You lost!')
                break
            else:
                if len(self.user.found_words) == self.WORDS_LIMIT:
                    self.success('Game over! You won!')
                    break

    @staticmethod
    def print_rules():
        print(
            '\nWelcome to wordcollect!\n',

            'Rules:',
            '  * You are given a word at least 15 letters long.',
            '  * You need to compose 10 words from the letters of this word in no particular order.',
            '  * Composed word minimum length is 4 letters.',
            '  * Each letter can be only used once unless it is repeated in the word.\n',

            'Commands:',
            '  * m - show mistakes left',
            '  * w - show words left',
            '  * f - show found words',
            '  * q - quit',

        sep='\n', end='\n\n')


if __name__ == '__main__':
    Game().mainloop()
