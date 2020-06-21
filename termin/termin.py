#!/usr/bin/python3

# This script prints programming termins in green with
# their definitions in white from the file terms.txt.
# flags -t --termin "termin" -a --all -v --verbose

import sys
import argparse

import colorama


def main():
    colorama.init(autoreset=True)
    args = parse_args()
    terms, defs = load_terms_defs()
    if args.termin:
        find_term(terms, defs, args.termin.lower(),
                  args.verbose)
    elif args.all:
        for i in range(len(terms)):
            print_term(terms[i])
            print(defs[i])
    colorama.deinit()
    sys.exit(0)


def find_term(terms: list, defs: list, termin: str, verbose: bool) -> None:
    """ Finds definition for the provided termin and prints it. """
    from colorama import Style, Fore
    for i, term in enumerate(terms):
        if term == termin:
            print_term(term)
            print(defs[i])
            return
    print("No information")
    if verbose and len(termin) >= 3:
        for term in terms:
            if term in termin or termin in term:
                fterm = Style.BRIGHT + Fore.GREEN + term + Style.RESET_ALL
                ans = input("Did you mean " + fterm + "? ").lower()
                if ans == "y" or ans == "yes":
                    print_term(term)
                    print(defs[i])
                    return


def load_terms_defs() -> tuple:
    """
        Loads termins and their respective defenitions from the textfile and
        Returns them as a tuple of lists.
        terms - termins list;
        defs - definitions list;
    """
    # I had to put my absolute path to this file in order to run
    # this script from everywhere in the system.
    # So change it for your preferrable place, otherwise it will be
    # anticipating to find this file in the directory where you would run it.
    fpath = "database.txt"
    try:
        with open(fpath, "r") as f:
            terms, defs = [], []
            for line in f:
                if line.startswith("    "):
                    defs.append(line.strip().lower())
                else:
                    terms.append(line.strip().lower())
    except FileNotFoundError:
        print(f"Unable to locate {fpath} file.")
        sys.exit(1)
    if len(terms) != len(defs):
        print(f"Error while processing {fpath} file.")
        print("Make sure there is no '\\n' at the end of the file.")
        sys.exit(1)
    return terms, defs


def print_term(input: str) -> None:
    """ Prints termin in specified color. """
    from colorama import Style, Fore
    print(Style.BRIGHT + Fore.GREEN + input.capitalize() + " ", end="")


def parse_args() -> argparse.Namespace:
    """ Parses optional command line arguments if provided. """
    description = ("Prints all programming termins in green with definitions "
                   "in white from the file terms.txt. Can print a specific "
                   "termin provided with -t flag.")
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument("-t", "--termin", help='Termin you are looking for.')
    parser.add_argument("-a", "--all", action="store_true",
                        help='Will print all termins from tems.txt.')
    parser.add_argument("-v", "--verbose", action="store_true",
                        help="Will thoroughly search for the definition in terms.txt.")
    args = parser.parse_args()
    if not args.termin and not args.all:
        parser.print_usage()
        sys.exit(1)
    return args


if __name__ == "__main__":
    main()
