#include "main.h"

/**
 * shell - a simple terminal
 * @argv: pointer list of args
 * Return: 0
 */
int shell(char **argv)
{
	size_t buffsize = 0;
	char *buff = NULL, *cmd, *tmp;
	int tty;

	tty = isatty(STDIN_FILENO);

	if (tty == 2)
	{
		perror(argv[0]);
		return (2);
	}
	if (tty == 1)
	{
		while (1)
		{
			printf("$ ");
			getline(&buff, &buffsize, stdin);

			if (_strcmp(buff, "exit\n") == 0)
				break;

			tmp = prep_string(buff);
			cmd = is_cmd_exist(tmp);

			if (cmd == NULL)
				perror(argv[0]);
			else
			{
				command(cmd);
				free(buff);
				free(cmd);
			}
		}
		return (0);
	}
	else
		non_interactive(argv);
	return (0);
}
/**
 * non_interactive - shell functionality for non interactive mode
 *
 * @argv: pointer array of args
 * Return: 0
 */
int non_interactive(char **argv)
{
	size_t buffsize = 0;
	char *buff = NULL, *tmp, *cmd;

	while (getline(&buff, &buffsize, stdin) != -1)
	{
		if (_strcmp(buff, "exit\n") == 0)
			break;

		tmp = prep_string(buff);
		cmd = is_cmd_exist(tmp);

		if (cmd == NULL)
			perror(argv[0]);
		else
		{
			command(cmd);
			free(buff);
			free(cmd);
		}
	}
	return (0);
}

/**
 * prep_string - takes a string, replaces newline with null byte
 *
 * @cmd: command to prep
 * Return: pointer to first char of cmd
 */
char *prep_string(char *cmd)
{
	int i;

	while (*cmd == ' ')
		cmd++;

	for (i = 0; i < _strlen(cmd); i++)
	{
		if (cmd[i] == '\n' || cmd[i] == ' ')
		{
			cmd[i] = '\0';
			return (cmd);
		}
	}
	return (cmd);
}

/**
 * is_cmd_exist - check if cmd exists in path or current directory
 *
 * @cmd: cmd to check
 * Return: pointer to cmd
 */
char *is_cmd_exist(char *cmd)
{
	struct stat st;
	char *env_path_var, *arg, *full_path;

	if (stat(cmd, &st) == 0)
		return (cmd);

	env_path_var = _strdup(getenv("PATH")); /* getenv - not allowed */
	arg = strtok(env_path_var, ":\0\n");

	while (arg != NULL)
	{
		full_path = strcpycat(arg, cmd);
		if (stat(full_path, &st) == 0)
		{
			/* found path */
			free(env_path_var);
			return (full_path);
		}

		arg = strtok(NULL, ":\0\n");
		free(full_path);
	}

	free(env_path_var);
	return (NULL);
}

/**
 * command - execute cmd
 * @cmd: command to execute
 * Return: 0
 */
int command(char *cmd)
{
	pid_t my_pid;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	my_pid = fork();
	if (my_pid == -1)
	{
		return (EXIT_FAILURE);
	}
	if (my_pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error: execve failed in command function.");
			exit(99);
		}
	}
	else
	{
		wait(NULL);
	}

	return (EXIT_SUCCESS);
}
