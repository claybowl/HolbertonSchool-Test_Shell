#include "main.h"
/**
 * strcpycat - make new string, append str to dest
 *
 * @dest: string from PATH
 * @str: command
 * Return: pointer to new string
 */
char *strcpycat(char *dest, char *str)
{
	char *new_str = NULL;
	int i = 0, x = 0;

	new_str = malloc((_strlen(dest) + _strlen(str) + 2) * sizeof(char));

	if (new_str == NULL)
	{
		/* malloc fail */
		perror("Malloc Fail in strcpycat()");
		return (NULL);
	}

	while (dest[i])
	{
		new_str[i] = dest[i];
		i++;
	}
	new_str[i] = '/';
	i++;
	while (str[x])
	{
		new_str[i + x] = str[x];
		x++;
	}
	new_str[i + x] = '\0';

	return (new_str);
}

/**
  * _strlen - gets legnth of string
  * @s: string to get legnth of
  * Return: int
  */
int _strlen(char *s)
{
	int i = 0;

	while (*s++)
		i++;
	return (i);
}

/**
  * _strcmp - compares two strings
  * @s1: string one
  * @s2: strint two
  * Return: int
  */
int _strcmp(char *s1, char *s2)
{
	int x = 0;

	while (s1[x] != '\0' && s2[x] != '\0')
	{
		if ((s1[x] - s2[x]) != 0)
			return (-1);
		x++;
	}

	return (0);
}

/**
  * _strdup - duplicate input to new string
  * @str: input string
  * Return: pointer to array, or NULL
  */
char *_strdup(char *str)
{
	char *s = NULL;
	unsigned int i = 0, size = 0;

	if (str == NULL)
		return (NULL);

	size = 0;
	while (str[size])
		size++;


	s = malloc((size + 1) * sizeof(char));

	if (s == NULL)
		return (NULL);

	i = 0;
	while (i < size)
	{
		s[i] = str[i];
		i++;
	}

	return (s);

}

/**
* g_env - getting env variable
* Return: 0.
*/
int g_env(void)
{
	unsigned int i = 0;

	for (; environ[i] != NULL; i++)
	{
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
	}
	return (0);
}
