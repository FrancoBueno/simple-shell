#ifndef HOLBERTON
#define HOLBERTON

#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void set_col(int c);
char *get_env(char *str);
char **str_to_arguments(char *buffer, char sep);
int search_bulit_in(char **arguments, char **env);
int search_command(char **arguments, char **env);
int search_file(char **arguments, char **env);
char *mystrcat(char *a, char *b);
#endif
