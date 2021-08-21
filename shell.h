#ifndef SHELL
#define SHELL

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

int _strlen(char *s);
unsigned int _strlen_const(const char *str);
int _strcmp(char *s1, char *s2);
void freearv(char **arv);
unsigned int length_of_command(char *string);
char *_strncpy(char *dest, char *src, int n);
char *_strncpyconst(char *dest, const char *src, int n);
unsigned int find_length_command(char *s);
void parent_free_commands(char *buffer, char **commands);
void send_to_free(char *buffer, char **commands);
void end_file(char *buffer);
void execute(char **commands, char *buffer, char **env,
		char **argv, int count);
/*env_functions.c*/
unsigned int find_num_dir(char *path);
char **store_e_variables(char *fir_com, char **environ);
char *_getenv(const char *name, char **environ);
char *_strncpcommand(char *dest, char *src, char *command, int n, int c);
void print_env(char **environ);

void build_message(char **av, char *fir_com, int count);
int _puterror(char c);
void end_file(char *buffer);
void fork_fail(void);

void null_command(char *buffer);
void get_out(char *buffer, char **commands);
void env_end(char *buffer, char **commands, char **env);
void _path(char **commands, char *buffer, char **env, char **argv, int count);

#endif
