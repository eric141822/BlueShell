#ifndef CMDS_H
#define CMDS_H

extern char *custom_cmds[];

int shell_exit(char **args);
int shell_help(char **args);
int shell_hello(char **args);
int shell_cflags(char **args);
int shell_mkdir(char **args);
int shell_rmdir(char **args);

extern int (*custom_func[])(char **);

int num_custom_cmds();


#endif /* CMDS.H */