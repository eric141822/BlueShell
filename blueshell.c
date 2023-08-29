#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 64
#define TOK_DELIM " \t\r\n\a"

// main shell loop. reads line, parses args, and executes
void shell_loop(void);
char *shell_line(void);
char **shell_get_args(char *line);
int shell_exec(char **args);

// custom command definitions
int shell_exit(char **args);
int shell_help(char **args);
int shell_hello(char **args);

// number of custom commands
int num_custom_cmds();

// order must match custom_func
char *custom_cmds[] = {"exit", "help", "hello"};

int (*custom_func[])(char **) = {
    shell_exit,
    shell_help,
    shell_hello,
};

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

int num_custom_cmds()
{
    return sizeof(custom_cmds) / sizeof(char *);
}

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

    for (int i = 0; i < num_custom_cmds(); i++)
    {
        if (strcmp(args[0], custom_cmds[i]) == 0)
        {
            return (*custom_func[i])(args);
        }
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

    int status;

    do
    {
        printf("> ");
        char *line = shell_line();
        char **args = shell_get_args(line);
        status = shell_exec(args);

        free(line);
        free(args);

    } while (status);
}

int main(void)
{
    shell_loop();
    return 0;
}
