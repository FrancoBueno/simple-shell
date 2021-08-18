#include "shell.h"
#include <signal.h>

int get_inp(void);
void prompt(int n);
int command(char **arguments, char **env);
int main(int argc, char **argv, char **env)
{
	int error = 1;

	signal(SIGINT, SIG_IGN);
	while (error == 1)
		error = get_inp();
	return (0);
}
int get_inp(void)
{
	char *buffer;
	extern char **environ;
	char **arguments;
	int i, error, inte;
	size_t characters, buf_size = 1024;

	buffer = malloc(buf_size);
	if (!buffer)
		return (-1);
	inte = isatty(0);
	prompt(inte);
	characters = getline(&buffer, &buf_size, stdin);
	if (buffer[characters - 1] == '\n')
		buffer[characters - 1] = 0;
        arguments = str_to_arguments(buffer, ' ');
	free(buffer);
	if (!arguments)
		return (-1);
	error = command(arguments, environ);
	for(i = 0; arguments[i]; i++)
		free(arguments[i]);
	free(arguments);
	return (inte ? error : 0);
}
int command(char **arguments, char **env)
{
	int i;

	i = search_bulit_in(arguments, env);
	if (i != 0)
		return (i);
	i = search_command(arguments, env);
	if (i != 0)
		return (i);
	i = search_file(arguments, env);
	if (i != 0)
		return (i);
	printf("./shell: No such file or directory\n");
	return (1);
}
void prompt(int n)
{
	char cwd[201];
	int i;

	if (n)
	{
	getcwd(cwd, 256);
	for (i = 0; cwd[i]; i++)
		;
	set_col(4);
	write(1, cwd, i);
	set_col(1);
	write(1, "$ ", 2);
	set_col(0);
	}
}
