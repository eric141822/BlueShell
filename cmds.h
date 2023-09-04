#ifndef CMDS_H
#define CMDS_H

int shell_exit(void);
int shell_help(void);
int shell_hello(char **argv);
int shell_cflags(char **argv);
int shell_mkdir(char **argv);
int shell_rmdir(char **argv);
int shell_ls(char **argv);
int shell_blue_shell(void);
int shell_cd(char **argv);

#endif /* CMDS.H */
