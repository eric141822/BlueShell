#ifndef CMDS_H
#define CMDS_H

int shell_exit();
int shell_help();
int shell_hello(char **argv);
int shell_cflags(char **argv);
int shell_mkdir(char **argv);
int shell_rmdir(char **argv);
int shell_ls(char **argv);


#endif /* CMDS.H */