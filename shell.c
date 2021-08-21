#include "shell.h"

/**
 * prompt - display prompt
 *
 * Return: void
 */
void prompt(void)
{
	char *str = "$ ";

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, str, 2);
}

/**
 * parse_input - gets and parses a line from the prompt
 * @str: line to parse
 *
 * Return: Array of tokens to be executed
 */
char **parse_input(char *str)
{
	char *token, **holder;
	unsigned int length;
	int i = 0;

	str[_strlen(str) - 1] = '\0'; /**replace the new line by null*/
	length = length_of_command(str);
	if (length == 0)
		return (NULL);
	holder = malloc((sizeof(char *) * (length + 1)));
	if (holder == NULL)
		return (NULL);
	token = strtok(str, " ");
	while (token != NULL)
	{
		holder[i] = malloc(_strlen(token) + 1);
		if (holder[i] == NULL)
		{
			freearv(holder);
			return (NULL);
		}
		_strncpy(holder[i], token, _strlen(token) + 1);
		token = strtok(NULL, " ");
		i++;
	}
	holder[i] = NULL;
	return (holder);
}

/**
* execute - Function to verify and execute every command
*@commands: command get
*@buffer: command in getline
*@env: enviroment variable
*@argv: argument counter
*@count: number of times that executed
*Return: Nothing(void)
*/

void execute(char **commands, char *buffer, char **env, char **argv, int count)
{
	struct stat fileStat;

	/*check if command is NULL or empty spaces*/
	if (commands == NULL)
		null_command(buffer);
	/*check if command is exit to exit from shell*/
	else if (_strcmp("exit", commands[0]))
		get_out(buffer, commands);
	/* check if the command is ENV to print environment variables */
	else if (_strcmp("env", commands[0]))
		env_end(buffer, commands, env);
	/*check if the command is a full path to an executable file*/
	else if (stat(commands[0], &fileStat) == 0)
		execve(commands[0], commands, NULL);
	/*check all $PATH directories for executable commands*/
	else
		_path(commands, buffer, env, argv, count);
}

/**
 * signal_handler - handles signals and write the prompt
 * @sig: signal to handle
 *
 * Return: void
 */
void signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: array of arguments
 * @env: pointer to list of env variables:wq
 *
 *
 * Return: 0 on Success or 1 if Error
 */
int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	size_t len = 0;
	ssize_t chars;
	pid_t pid;
	char **tokens, *line = NULL;
	int i = 0, status;

	(void)argc;
	prompt();
	for (; (chars = getline(&line, &len, stdin)); )
	{
		signal(SIGINT, signal_handler); /*CTRL+C*/
		if (chars == EOF)
			end_file(line);
		i++;
		tokens = parse_input(line);
		pid = fork();
		if (pid == -1)
			fork_fail();
		if (pid == 0)
			execute(tokens, line, env, argv, i);
		else
		{
			wait(&status);
			send_to_free(line, tokens);
		}
		len = 0, line = NULL;
		prompt();
	}
	if (chars == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
