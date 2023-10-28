#ifndef CMDS_H
#define CMDS_H

// exits the custom shell.
int shell_exit(void);

// shows available custom commands and usage.
int shell_help(void);

// says hello to you!.
int shell_hello(char **argv);

// A collection of gereral and best practice compiler flags for C and C++ (gcc and g++).
int shell_cflags(char **argv);

// creates a new directory.
int shell_mkdir(char **argv);

// removes a directory.
int shell_rmdir(char **argv);

// lists the files in specified path. Supports -l flag.
int shell_ls(char **argv);

// easter egg :).
int shell_blue_shell(void);

// changes the current working directory to *path*.
int shell_cd(char **argv);

#endif /* CMDS.H */
