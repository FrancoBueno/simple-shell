#include "shell.h"

void execute(char **arguments, char **env)
{
	int pid, exit_status;

	pid = fork();
	if (pid == 0)
	{
		execve(arguments[0], arguments, env);
		exit(0);
	}
	else
		wait(&exit_status);
}
void execute_built_in(int n, char **arguments, char **env)
{
	switch (n)
	{
	case 0:
		chdir(arguments[1]);
		break;
	case 1:
		exit(0);
	}
}
int search_bulit_in(char **arguments, char **env)
{
	int i;
	char *commands[] = {"cd",
			    "exit",
			    "history",
			    "help",
			    NULL};
	for (i = 0; commands[i]; i++)
		if (strcmp(commands[i], arguments[0]) == 0)
		{
			execute_built_in(i, arguments, env);
			return (1);
		}
	return (0);
}
int search_command(char **arguments, char **env)
{
	char *path, *command, *first_arg;
	struct stat statbuf;
	char **paths;
	int i, found = 0, file;

	path = get_env("PATH");
	paths = str_to_arguments(path, ':');
	if (!paths)
		return (0);
	for (i = 0; paths[i] && !found; i++)
	{
		command = mystrcat(paths[i], arguments[0]);
		if (command)
		{
			file = stat(command, &statbuf);
			if (file == 0)
			{
				first_arg = arguments[0];
				arguments[0] = command;
				execute(arguments, env);
				arguments[0] = first_arg;
				found = 1;
			}
		}
		free(command);
	}
	for(i = 0; paths[i]; i++)
		free(paths[i]);
	free(paths);
	return (found);
}
int search_file(char **arguments, char **env)
{
	int file;
	struct stat statbuf;

	file = stat(arguments[0], &statbuf);
	if (file == 0)
	{
		execute(arguments, env);
		return (1);
	}
	return (0);
}
