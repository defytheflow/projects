#!/usr/bin/python3

# TODO implement -s option

import sys
from typing import List

def main(argv: List[str]):

    opts: List[str] = []
    args: List[str] = []

    for arg in argv:
        if arg.startswith('-'):
            opts.append(arg)
        else:
            args.append(arg)

    f_contents: List[str] = []

    for f_name in args:
        load_file(f_name, f_contents)

    for opt in opts:
        if opt == '-b':
            add_line_numbers(f_contents, empty_lines=False)
        if opt == '-n':
            add_line_numbers(f_contents, empty_lines=True)
        if opt == '-t':
            add_tabs(f_contents)
        if opt == '-E':
            add_ends(f_contents)

    for line in f_contents:
        print(line)


def load_file(f_name: str, f_contents: List[str]):
    ''' '''
    try:
        with open(f_name, 'r') as f:
            f_contents.extend([line.rstrip() for line in f.readlines()])
    except FileNotFoundError:
        print(f"Error: file '{f_name}' not found.", file=sys.stderr)
    except IsADirectoryError:
        print(f"Error: '{f_name}' is a directory.", file=sys.stderr)


def add_line_numbers(f_contents: List[str], empty_lines: bool=True):
    ''' '''
    if empty_lines:
        for i, line in enumerate(f_contents):
            f_contents[i] = '    ' + str(i + 1) + '  ' + line
    else:
        line_num = 1
        for i, line in enumerate(f_contents):
            if len(line) > 0 and not line.isspace():
                f_contents[i] = '    ' + str(line_num) + '  ' + line
                line_num += 1


def add_tabs(f_contents: List[str]):
    ''' '''
    for i, line in enumerate(f_contents):
        if '\t' in line:
            f_contents[i] = line.replace('\t', '^I')


def add_ends(f_contents: List[str]):
    ''' '''
    for i, line in enumerate(f_contents):
        f_contents[i] = line + '$'


if __name__ == '__main__':
    main(sys.argv[1:])
