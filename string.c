#include "main.h"

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

	while (s1[x] != '\0')
	{
		if ((s1[x] - s2[x]) != 0)
			break;
		x++;
	}

	return (s1[x] - s2[x]);
}

/**
  * _strdup - duplicate input to new string
  * @str: input string
  * Return: pointer to array, or NULL
  */
char *_strdup(char *str)
{
	char *s;
	unsigned int i, size;

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
