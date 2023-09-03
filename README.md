# Blueshell

Custom shell written in C.

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
