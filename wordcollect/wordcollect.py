#!/usr/bin/python3

'''
    File:     wordcollect.py
    Created:  23.06.2019
    Updated:  21.06.2020
    Author:   Artyom Danilov
'''

import bisect
import random
import readline
import sys
import string

import colorama


class Commands:

    FOUND    = 'f'
    MISTAKES = 'm'
    QUIT     = 'q'

    @classmethod
    def is_command(cls, string):
        return string in cls.__dict__.values()

    @classmethod
    def execute(cls, command, game):
        if command == cls.FOUND:
            game.printer.info(f'Found words: {game.user.found_words}')
        elif command == cls.MISTAKES:
            game.printer.info(f'Mistakes: {game.user.mistakes}')
        elif command == cls.QUIT:
            sys.exit(0)
        else:
            raise ValueError("Unknown command - '{command}'")


class Settings:

    MISTAKES_LIMIT  = 10
    WORDS_LIMIT     = 10
    WORD_MIN_LENGTH = 4


class Utils:

    @staticmethod
    def bsearch(seq, item):
        i = bisect.bisect_left(seq, item)
        return i if (i != len(seq) and seq[i] == item) else -1

    @staticmethod
    def keychoice(seq, key):
        while True:
            element = random.choice(seq)
            if key(element):
                return element

    @staticmethod
    def is_ascii_lowercase(word):
        return all(char in string.ascii_lowercase for char in word)

    @staticmethod
    def freadlines(fname):
        with open(fname) as file:
            return file.readlines()


class Printer:

    colors = {
        'error':   colorama.Fore.RED,
        'info':    colorama.Fore.BLUE,
        'primary': colorama.Fore.MAGENTA,
        'success': colorama.Fore.GREEN,
        'warning': colorama.Fore.YELLOW,
    }

    def __init__(self):
        colorama.init()

    def error(self, *args, **kwargs):
        self._print('error', *args, **kwargs)

    def info(self, *args, **kwargs):
        self._print('info', *args, **kwargs)

    def primary(self, *args, **kwargs):
        self._print('primary', *args, **kwargs)

    def success(self, *args, **kwargs):
        self._print('success', *args, **kwargs)

    def warning(self, *args, **kwargs):
        self._print('warning', *args, **kwargs)

    def _print(self, category, *args, prefix=False, command=lambda: None, **kwargs):
        command()
        print(self.colors[category], f'{category.title()}: ' if prefix else '', sep='', end='')
        print(*args, colorama.Style.RESET_ALL, **kwargs)


class User:

    def __init__(self):
        self.mistakes = 0
        self.found_words = []

    def inc_mistakes(self):
        self.mistakes += 1


class MistakesLimitExceededError(Exception):
    pass


class Game:

    def __init__(self):
        self.user = User()
        self.printer = Printer()
        self.words = Utils.freadlines('words.txt')
        self.game_word = Utils.keychoice(self.words, key=lambda word: len(word) >= 10).strip()
        self.print_rules()

    def mainloop(self):
        while True:
            try:
                self.prompt_user('Found word: ')
            except MistakesLimitExceededError:
                self.printer.error('Game over! You lost!')
                break
            else:
                if len(self.user.found_words) == Settings.WORDS_LIMIT:
                    self.printer.success('Game over! You won!')
                    break

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

            if self.user.mistakes == Settings.MISTAKES_LIMIT:
                raise MistakesLimitExceededError()

            self.printer.primary(f'[ {self.game_word.upper()} ]: ', end='')
            user_word = input().strip().lower()

            if not user_word:
                self.printer.error('blank input.\n', prefix=True, command=self.user.inc_mistakes)
                continue

            if Commands.is_command(user_word):
                Commands.execute(user_word, self)
                continue

            if not Utils.is_ascii_lowercase(user_word):
                self.printer.error('invalid english word.\n', prefix=True, command=self.user.inc_mistakes)
                continue

            if len(user_word) < Settings.WORD_MIN_LENGTH:
                self.printer.error('short word.\n', prefix=True, command=self.user.inc_mistakes)
                continue

            if len(user_word) >= len(self.game_word):
                self.printer.error('long word.\n', prefix=True, command=self.user.inc_mistakes)
                continue

            if Utils.bsearch(self.words, f'{user_word}\n') == -1:
                self.printer.error('word does not exist in the game dictionary.\n',
                                   prefix=True,
                                   command=self.user.inc_mistakes)
                continue

            if user_word in self.user.found_words:
                self.printer.error('word already found.\n', prefix=True, command=self.user.inc_mistakes)
                continue

            if not self.word_can_be_composed(user_word):
                self.printer.error('cannot compose word.\n', prefix=True, command=self.user.inc_mistakes)
                continue

            self.printer.success('correct!', command=lambda: self.user.found_words.append(user_word))


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

            sep='\n', end='\n\n'
        )


if __name__ == '__main__':
    Game().mainloop()
