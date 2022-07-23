#include "main.h"

/**
 * main - simple shell main
 *
 * Return: always 0
 */
int main(void)
{
	size_t buffsize;
	char *buff, *cmd;

	while (1)
	{
		printf("($) ");
		getline(&buff, &buffsize, stdin);

		if (strcmp (buff, "exit\n") == 0)
			break;

		cmd = prep_string(buff);
		/* add a check if cmd exists or exists in $PATH */
		command(cmd);
	}
	return (0);
}

/**
 * prep_string - takes a 1 arg command and preps it for execve
 *
 * @cmd: command to prep
 * Return: pointer to first char of cmd
 */
char *prep_string(char *cmd)
{
	int i;
	/* set cmd pointer to first real char */
	while (*cmd == ' ')
		cmd++;

	for (int i = 0; i < strlen(cmd); i++)
	{
		if (cmd[i] == '\n')
		{
			cmd[i] = '\0';
			return (cmd);
		}
	}

	return (cmd);
}

int command(char *cmd)
{
	pid_t my_pid;
	char *argv[] = {cmd, NULL};

	my_pid = fork();
	if (my_pid == -1)
	{
		/* error */
		return (EXIT_FAILURE);
	}
	if (my_pid == 0)
	{
		/* child */
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error: execve failed in command function.");
			exit(99);
		}
	}
	else
	{
		/* parent */
		wait(NULL);
	}
}
