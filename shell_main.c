#include "main.h"

/**
 * main - main function
 * @ac: unsused # of vars
 * @av: pointer array of args
 * Return: always 0
 */
int main(__attribute__((unused))int ac, char **av)
{
	if (av[0])
		shell(av);
	return (EXIT_SUCCESS);
}
