#!/bin/bash

# A small library for bash scripts.
#
# Modified by Artyom Danilov on January 2, 2020.
#

# error function increments this variable every call
NUM_ERRORS=0

# Returns text highlighted with white background
reversed() {
    echo -e "\033[7m$1\033[0m"
}

# Returns text in green color
green() {
    echo -e "\033[0;32m$1\033[0m"
}


# Reports an error in red color and exits the program
fatal_error() {
    printf "\033[1;31mError:\033[0m $1\n" 1>&2
    exit 1
}

# Just reports an error in red color
error() {
    printf "\033[1;31mError:\033[0m $1\n" 1>&2
    NUM_ERRORS=$((NUM_ERRORS + 1))
}

# Reports a fix in green color
fix() {
    printf "\033[0;32mFix:\033[0m $1\n" 1>&2
}

# Reports a warning in yellow
warning() {
    printf "\033[1;33mWarning:\033[0m $1\n" 1>&2
}

# Prompts user if to proceed or not.
ask() {
    echo -n "$1? [y/n]: "
    read ANS
    if [[ ! "$ANS" =~ ^[yY][eE]?[sS]?$ ]]; then
            exit 0
    fi
}

# Hides a file
hide() {
    for file in $@; do
        if [[ ${file::1} != . ]]; then
            mv $file .$file
        fi
    done
}
export -f hide

# Shows a hidden file
show() {
    for file in $@; do
        if [[ ${file::1} == . ]]; then
            mv $file ${file/./}
        fi
    done
}
export -f show
