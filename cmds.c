#include "cmds.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

char *custom_cmds[] = {"exit", "help", "hello", "cflags", "mkdir", "rmdir", "ls"};

int shell_exit()
{
    return 0;
}
int shell_help()
{
    printf("Welcome to Blueshell!\n");
    printf("Custom commands supported:\n");
    for (int i = 0; i < num_custom_cmds(); i++)
    {
        printf("%s\n", custom_cmds[i]);
    }
    return 1;
}

int shell_hello(char **argv)
{
    if (argv[1] == NULL)
    {
        printf("cmd: hello requires an argument, how can I say hello without your name? :)\n");
    }
    else
    {
        printf("Hello, %s!\n", argv[1]);
    }
    return 1;
}

int shell_cflags(char **argv)
{
    if (argv[1] == NULL)
    {
        fprintf(stderr, "cflags: requires an argument\n");
    }
    else
    {
        if (strcasecmp(argv[1], "C") == 0)
        {
            printf("-Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align -pedantic -O3\n");
        }
        else if (strcasecmp(argv[1], "C++") == 0 || strcasecmp(argv[1], "CXX") == 0 || strcasecmp(argv[1], "CPP") == 0)
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

int shell_mkdir(char **argv)
{
    if (argv[1] == NULL)
    {
        fprintf(stderr, "mkdir: requires an argument\n");
    }

    struct stat st = {0};

    if (stat(argv[1], &st) == -1)
    {
        mkdir(argv[1], 0700);
    }
    else
    {
        fprintf(stderr, "mkdir: directory already exists\n");
    }

    return 1;
}

int shell_rmdir(char **argv)
{
    if (argv[1] == NULL)
    {
        fprintf(stderr, "rmdir: requires an argument\n");
    }

    struct stat st = {0};

    if (stat(argv[1], &st) == -1)
    {
        fprintf(stderr, "rmdir: directory does not exist\n");
    }
    else
    {
        rmdir(argv[1]);
    }
    return 1;
}

int shell_ls(char **argv) {
    // get opts.
    int opt;
    int aflag = 0;
    int lflag = 0;
    int argc;
    for (argc = 0; argv[argc] != NULL; argc++);
    while ((opt = getopt(argc, argv, "al")) != -1) {
        switch (opt) {
            case 'a':
                aflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            default:
                fprintf(stderr, "ls: invalid option\n");
                return 1;
        }
    }

    char *path = argv[optind];
    // reset optind.
    optind = 1;
    struct stat st;
    
    if (stat(path, &st) == -1) {
        fprintf(stderr, "ls: directory does not exist\n");
        return 1;
    }
    // get dir.
    DIR *dr = opendir(path);
    struct dirent *de;

    // if (dr) {
    //     while ((de = readdir(dr)) != NULL) {
    //         printf("%s\n", de->d_name);
    //     }
    //     closedir(dr);
    // }

    return 1;
}


int num_custom_cmds()
{
    return sizeof(custom_cmds) / sizeof(char *);
}
