# Blueshell

Custom shell written in C.

A simple practice/study, following the fantasic [guide](https://brennan.io/2015/01/16/write-a-shell-in-c/) by [Stephen Brennan](https://brennan.io/).

## Implemented CMDs

- help
    - prints the list of commands available.
- exit
    - quits the shell, same as `ctrl/cmd+c`.
- hello *arg*
    - prints a hello message to *arg*.
- cflags *arg*
    - prints a list of commonly used flags for gcc and g++ compilers.
        - *arg* can be C or C++/CXX/CPP (case insentisive).
- mkdir
    - creates a directory.
- rmdir
    - removes a directory.
- ls
    - prints a list of files and folders in the specified path. Supports the -l flag.
