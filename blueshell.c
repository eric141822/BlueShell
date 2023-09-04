#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "cmds.h"

#define BUFFER_SIZE 64
#define TOK_DELIM " \t\r\n\a"

// main shell loop. reads line, parses args, and executes
void shell_loop(void);
char *shell_line(void);
char **shell_get_args(char *line);
int shell_exec(char **args);

char *shell_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

char **shell_get_args(char *line)
{
    int bufsize = BUFFER_SIZE;
    char **tokens = malloc(bufsize * sizeof(char *));

    if (!tokens)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    int pos = 0;

    char *token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[pos++] = token;

        if (pos >= bufsize)
        {
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
        }

        token = strtok(NULL, TOK_DELIM);
    }

    // null terminate for args
    tokens[pos] = token;

    return tokens;
}

int shell_exec(char **args)
{
    if (args[0] == NULL)
    {
        return 1; // continue the loop in shell_loop.
    }

    if (strcmp(args[0], "exit") == 0)
    {
        return shell_exit();
    }
    else if (strcmp(args[0], "help") == 0)
    {
        return shell_help();
    }
    else if (strcmp(args[0], "hello") == 0)
    {
        return shell_hello(args);
    }
    else if (strcmp(args[0], "cflags") == 0)
    {
        return shell_cflags(args);
    }
    else if (strcmp(args[0], "mkdir") == 0)
    {
        return shell_mkdir(args);
    }
    else if (strcmp(args[0], "rmdir") == 0)
    {
        return shell_rmdir(args);
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        return shell_ls(args);
    }
    else if (strcmp(args[0], "blueshell") == 0)
    {
        return shell_blue_shell();
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        return shell_cd(args);
    }

    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        // child
        if (execvp(args[0], args) == -1)
        {
            perror("execvp error");
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid < 0)
    {
        perror("fork error");
    }
    else
    {
        // parent
        int status;
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

void shell_loop(void)
{
    printf("*****************\n");
    printf("*** BLUESHELL ***\n");
    printf("*****************\n");

    int status = 1;

    while (status)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s", cwd);
        }
        else
        {
            perror("getcwd error");
        }

        printf("> ");
        char *line = shell_line();
        char **args = shell_get_args(line);
        status = shell_exec(args);
        free(line);
        free(args);
    }
}

int main(void)
{
    shell_loop();
    return 0;
}
