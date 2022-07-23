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

/* function prototypes */
int command(char *cmd);
char *prep_string(char *cmd);





#endif
