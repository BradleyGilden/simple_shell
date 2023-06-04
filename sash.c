#include "sash.h"
#include <stdlib.h>

/**
 * handle_sigint - signal handler function
 * @sig: signal argument
 */

void handle_sigint(int __attribute__((unused))sig)
{
	char *prompt = "\n✔ <0> $ ";
	signal(sig, handle_sigint);
	w_out(prompt);
}

/**
 * main - handles the mode of the shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 Always
 */

int main(int __attribute__((unused))argc, char *argv[])
{
	if (argv == NULL || *argv == NULL)
		exit(EXIT_FAILURE);

	signal(SIGINT, handle_sigint);
	my_getline(argv[0]);

	return (0);
}
