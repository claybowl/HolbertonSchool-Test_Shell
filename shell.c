#include "main.h"

/**
 * main - shell main func
 * @ac: unused
 * @argv: pointer list of args
 * Return: 0
 */
int main(__attribute__((unused))int ac, char **argv)
{
	int tty = 0;

	tty = isatty(STDIN_FILENO);
	if (tty == 2)
	{
		perror(argv[0]);
		return (2);
	}
	else
		shell(argv, tty);

	return (0);
}
/**
 * shell - high level shell loop
 *
 * @argv: pointer array of args
 * @tty: is/is not tty
 * Return: 0
 */
int shell(char **argv, int tty)
{
	size_t buffsize = 0;
	char *buff = NULL, *tmp = NULL; /**cmd = NULL*/
	int valid_input = 1;
	while (valid_input)
	{
		if (tty == 1)
			printf("$ ");
		
		valid_input = getline(&buff, &buffsize, stdin);
		if (_strcmp(buff, "exit\n") == 0)
		{
			break;
		}
		tmp = prep_string(buff);
		
		if (tmp == NULL)
			perror(argv[0]);
		/*
		cmd = is_cmd_exist(tmp);
		
		if (cmd == NULL)
			perror(argv[0]);
		else
		{
			command(cmd);
			if (_strcmp(tmp, cmd) != 0)
				free(cmd);
		}
		*/
		command(tmp);
	}
	free(buff);
	buff = NULL;
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
	int i = 0;

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

	arg = strtok(env_path_var, ":");

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
