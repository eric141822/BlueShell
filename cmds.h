#ifndef CMDS_H
#define CMDS_H

extern char *custom_cmds[];

int shell_exit();
int shell_help();
int shell_hello(char **argv);
int shell_cflags(char **argv);
int shell_mkdir(char **argv);
int shell_rmdir(char **argv);
int shell_ls(char **argv);

extern int (*custom_func[])(char **);

int num_custom_cmds();


#endif /* CMDS.H */