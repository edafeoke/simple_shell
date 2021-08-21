#include "shell.h"

/**
 * freearv - frees the array of pointers arv
 *@arv: array of pointers
 */

void freearv(char **arv)
{
	int i;

	for (i = 0; arv[i]; i++)
		free(arv[i]);
	free(arv);
}

/**
* send_to_free - Function to send free when the child is not created
*@buffer: buffer created by getline
*@commands: array of commands
*Return: Nothing(void)
*/

void send_to_free(char *buffer, char **commands)
{
	if (commands == NULL)
		parent_free_commands(buffer, commands);
	/*on exit status*/
	else if (_strcmp("exit", commands[0]))
		get_out(buffer, commands);
	else
		parent_free_commands(buffer, commands);
}

/**
 * parent_free_commands - free the buffer and the commands
 * @buffer: buffer in getline
 * @commands: double pointer that store all the commands inserted
 * Return: Nothing(void)
*/

void parent_free_commands(char *buffer, char **commands)
{
	free(buffer);
	freearv(commands);
}
