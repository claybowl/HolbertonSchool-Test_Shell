#include "main.h"
/** THINGS 2 FIX:
*	- shell: uses printf, implement _printf (CLAYTON IS ON IT)
*	- is_cmd_exist: uses getenv, implement builtin? env func
*	- size of func? might need to make own
*	- handle EOF!
* 	- GLOBAL ARGV!
*/

/* char **argv; */

/**
 * main - main function
 * 
 * Return: always 0
 */
int main(int ac, char **av)
{
	shell(ac, av);
	return (EXIT_SUCCESS);
}

/**
 * shell - a simple terminal
 *
 * Return: 
 */
int shell(int ac, char **argv)
{
	size_t buffsize;
	char *buff, *cmd;
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
			printf("($) ");
			getline(&buff, &buffsize, stdin);

			if (_strcmp(buff, "exit\n") == 0)
				break;

			 cmd = prep_string(buff);
			 cmd = is_cmd_exist(cmd);

			 if (cmd == NULL)
				 perror(argv[0]);
			 else
				 command(cmd);
		}

		return (0);
	}
	else
	{
		while(getline(&buff, &buffsize, stdin) != -1)
		{
			if (_strcmp(buff, "exit\n") == 0)
				break;

			cmd = prep_string(buff);
			cmd = is_cmd_exist(cmd);

			if (cmd == NULL)
				perror(argv[0]);
			else
				command(cmd);
				free(cmd);
		}

		return(0);
	}
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

	for (int i = 0; i < _strlen(cmd); i++)
	{
		if (cmd[i] == '\n')
		{
			cmd[i] = '\0';
			return (cmd);	
		}
	}
	return (cmd);
}

char *is_cmd_exist(char *cmd)
{
	struct stat st;
	char *env_path_var, *arg, *full_path;

	if (stat(cmd, &st) == 0)
		return(cmd);

	env_path_var = _strdup(getenv("PATH")); /* getenv - not allowed in final project */
	arg = strtok(env_path_var, ":");


	while (arg != NULL)
	{
		full_path = strcpycat(arg, cmd);
		if (stat(full_path, &st) == 0)
		{
			/* found path */
			return (full_path);
		}

		free(full_path);
		arg = strtok(NULL, ":");
	}

	free(env_path_var);
	return (NULL);
}

int command(char *cmd)
{
	pid_t my_pid;
	char *argv[] = {cmd, NULL};

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

char *strcpycat(char *dest, char *str)
{
	char *new_str;
	int i = 0, x = 0;

	new_str = malloc((_strlen(dest) + _strlen(str) + 2) * sizeof(char));

	if (new_str == NULL)
	{
		/* malloc fail */
		perror("Malloc Fail in strcpycat()");
		return(NULL);
	}

	while(dest[i])
	{
		new_str[i] = dest[i];
		i++;
	}
	new_str[i] = '/';
	i++;
	while(str[x])
	{
		new_str[i + x] = str[x];
		x++;
	}
	new_str[i + x] = '\0';

	return (new_str);
}
