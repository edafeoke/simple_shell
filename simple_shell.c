#include "simple_shell.h"


/**
 * prompt - display prompt
 *
 * Return: void
 */
void prompt(void)
{
	char *str = "$ ";

	write(STDIN_FILENO, str, 3);
}

/**
 * parse_input - gets and parses a line from the prompt
 * @tokens: pointer to store the tokens
 *
 * Return: 0
 */
int parse_input(char __attribute__((unused)) **tokens)
{
	size_t len, i;
	size_t buf = 1024;
	char *token, *line;

	len = getline(&line, &buf, stdin);
	i = 0;
	token = strtok(line, " ");
	while (token)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (len);
}

/**
 * execute = executes parsed cli inputs
 * @tokens: input tokens
 *
 * Return: o on sucess and -1 on error
 */
int execute(char **cmd)
{
	pid_t child_pid;
	int status;

	if (strncmp("exit", cmd[0], 4) == 0)
		return (-1);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}
	else if (child_pid == 0)
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			perror("Error");
			exit(-1);
		}
	}
	else
		wait(&status);
	return (0);
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: array of arguments
 *
 * Return: 0
 */
int main(int __attribute__((unused)) argc, __attribute__((unused))char *argv[])
{
	char *tokens[1024];
	int i = 0;

	for (;;)
	{
		prompt();
		parse_input(tokens);
		/*execute(tokens);*/
		while (tokens[i])
		{
			i++;
		}
	}
	return (argc);
}
