#include "main.h"

/**
 * main - simple shell main
 *
 * Return: always 0
 */
int main(int ac, char **argv)
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
		 if (cmd == NULL)
		 {
			 printf("%s: 1: %s: not found\n", argv[0], cmd);
		 }
		 else
		 {
			 cmd = is_cmd_exist(cmd);
			 if (cmd == NULL)
				 printf("./ss: %s: Temporary Error Message, command %s not found.\n", buff, buff);
			 else
				 command(cmd);
		 }
		/* add a check if cmd exists or exists in $PATH */
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

char *is_cmd_exist(char *cmd)
{
	struct stat st;
	char *env_path_var, *arg, *full_path;

	env_path_var = strdup(getenv("PATH")); /* getend - not allowed in final project */
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

char *strcpycat(char *dest, char *str)
{
	char *new_str;
	int i = 0, x = 0;
	
	new_str = malloc((strlen(dest) + strlen(str) + 2) * sizeof(char));

	if (new_str == NULL)
	{
		/* malloc fail */
		printf("Mallac Fail in: strcpycat()");
		return(NULL);
	}
	
	while (dest[i])
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
