#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "shell.h"

int get_inp(char **env);
void init(void);
void command(char **arguments, char **env);
int main(int argc, char **argv, char **env)
{
	int error, exit_code = 0, fork_exit_code, i;
	char cwd[200];

	init();
	error = 1;
	while (error == 1)
		error = get_inp(env);
	return (0);
}
int get_inp(char **env)
{
	char *buffer;
	char **arguments;
	char cwd[201];
	int i;
	size_t characters, buf_size;

	buffer = malloc(buf_size);
	if (!buffer)
		return (-1);
	write(1, "$ ", 2);
	characters = getline(&buffer, &buf_size, stdin);
	if (buffer[characters - 1] == '\n')
		buffer[characters - 1] = 0;
        arguments = str_to_arguments(buffer);
	if (!arguments)
		return (-1);
	printf("<%s>\n", buffer);
	command(arguments, env);
	return (1);
}
void command(char **arguments, char **env)
{
	int i;

	for (i = 0; arguments[i]; i++)
		printf("<%s>\n", arguments[i]);
}
void init(void)
{
	int i;

	if (fork() == 0)
	{
		chdir("/root");
		exit(0);
	}
	else
		wait(&i);
}
