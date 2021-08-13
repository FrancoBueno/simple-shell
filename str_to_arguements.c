#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "shell.h"

char **str_to_arguments(char *buffer)
{
	char **out;
	int i, i2, i3, error, arg_amount = 1;
	char *ptr, *tmp;

	for (i = 0; buffer[i]; i++)
		if (buffer[i] == ' ')
			if (buffer[i + 1] && (buffer[i + 1] != ' '))
				arg_amount++;
	out = malloc((arg_amount + 1) * sizeof(char *));
	if (!out)
		return (out);
	out[arg_amount] = NULL;
	ptr = buffer;
	for (i = 0; i < arg_amount; i++)
	{
		while (ptr[0] == ' ')
			ptr = ptr + 1;
		printf("ptr: %s\n", ptr);
		for (i2 = 0; ptr[i2] && (ptr[i2] != ' '); i2++)
			;
		tmp = malloc(i2 + 1);
		tmp[i2] = 0;
		if (!tmp)
		{
			error = 1;
			break;
		}
		for (i3 = 0; i3 < i2; i3++)
			tmp[i3] = ptr[i3];
		printf("tmp: %s\n", tmp);
		ptr += i2;
		out[i] = tmp;
	}
	if (error)
	{
		for (i2 = 0; i2 < i; i2++)
			free(out[i2]);
		free(out);
	}
	return (out);
}
