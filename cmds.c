#include "cmds.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

char *custom_cmds[] = {"exit", "help", "hello", "cflags", "mkdir", "rmdir"};

int shell_exit(char **args)
{
    return 0;
}
int shell_help(char **args)
{
    printf("Welcome to Blueshell!\n");
    printf("Custom commands supported:\n");
    for (int i = 0; i < num_custom_cmds(); i++)
    {
        printf("%s\n", custom_cmds[i]);
    }
    return 1;
}

int shell_hello(char **args)
{
    if (args[1] == NULL)
    {
        printf("cmd: hello requires an argument, how can I say hello without your name? :)\n");
    }
    else
    {
        printf("Hello, %s!\n", args[1]);
    }
    return 1;
}

int shell_cflags(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "cflags: requires an argument\n");
    }
    else
    {
        if (strcasecmp(args[1], "C") == 0)
        {
            printf("-Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align -pedantic -O3\n");
        }
        else if (strcasecmp(args[1], "C++") == 0 || strcasecmp(args[1], "CXX") == 0 || strcasecmp(args[1], "CPP") == 0)
        {
            printf("-Wall -pedantic -Wshadow -O3 -std=c++17\n");
            printf("Add -g for debug symbols\n");
        }
        else
        {
            fprintf(stderr, "cflags: invalid argument\n");
        }
    }

    return 1;
}

int shell_mkdir(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "mkdir: requires an argument\n");
    }

    struct stat st = {0};

    if (stat(args[1], &st) == -1)
    {
        mkdir(args[1], 0700);
    }
    else
    {
        fprintf(stderr, "mkdir: directory already exists\n");
    }

    return 1;
}

int shell_rmdir(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "rmdir: requires an argument\n");
    }

    struct stat st = {0};

    if (stat(args[1], &st) == -1)
    {
        fprintf(stderr, "rmdir: directory does not exist\n");
    }
    else
    {
        rmdir(args[1]);
    }
    return 1;
}

int (*custom_func[])(char **) = {
    shell_exit,
    shell_help,
    shell_hello,
    shell_cflags,
    shell_mkdir,
    shell_rmdir,
};

int num_custom_cmds()
{
    return sizeof(custom_cmds) / sizeof(char *);
}