#ifndef MAIN_H
#define MAIN_H

/* standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

/* function prototypes */
int shell(char **argv, int tty);

int command(char *cmd);
char *prep_string(char *cmd);
char *is_cmd_exist(char *cmd);
char *strcpycat(char *dest, char *str);

/* string.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
#endif
