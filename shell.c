#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define TOK_BUF_SIZE 64
#define STR_TOKS "\t\r\n\a"

int lsh_launch(char **args)
{
    pid_t pid;

    int status;

    pid = fork();
    if (pid == 0)
    {
        // execvp(command, args array);
        if (execvp(args[0], args) == -1)
        {
            perror("execvp error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("fork error");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"};
// an array of function pointers (that take array of strings and return an int)
int (*builtin_func[])(char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit};
int lsh_num_builtins()
{
    return sizeof(builtin_func) / sizeof(char *);
}

int lsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    int i;

    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");
    for (i = 0; i < lsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}

// read line from input.
// since we don't know how long the input is, allocate more memory if input exceeds initial buffer.
char *lsh_read_line(void)
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

char **lsh_split_line(char *line)
{
    size_t bufsize = TOK_BUF_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));

    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, STR_TOKS);

    while (token != NULL)
    {
        tokens[position++] = token;

        if (position >= bufsize)
        {
            bufsize += TOK_BUF_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, STR_TOKS);
    }
    tokens[position] = NULL; // set last element to NULL, so we know where the array ends.
    return tokens;
}

int lsh_execute(char **args)
{
    int i;

    if (args[0] == NULL)
    {
        return 1;
    }

    for (i = 0; i < lsh_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }
    return lsh_launch(args);
}

// this function takes no arguments, instead of void foo() which takes unspecified amounts of arguments.
void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("@my-shell> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);

    } while (status);
}

int main(int argc, char **argv)
{
    lsh_loop();
    return EXIT_SUCCESS;
}