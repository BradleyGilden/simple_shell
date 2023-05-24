#include "main.h"

/**
 * free_alloced_mem_on_exit - free's all memory and sets it to null
 * @glob: struct of global variables
 */

void free_alloced_mem_on_exit(myglob_t *glob)
{
	if (glob->lineptr != NULL)
		free(glob->lineptr);
	if (glob->tokens != NULL)
		free_tokens(glob->tokens);
	if (glob->copy != NULL)
		free(glob->copy);
	glob->lineptr = NULL, glob->copy = NULL, glob->tokens = NULL;
}

/**
 * free_tokens - free's 2d array of tokens
 * @tokenarr: tokenized 2d array of line ptr string
 */

void free_tokens(char **tokenarr)
{
	int i = 0, len = 0;

	if (tokenarr == NULL)
		return;

	while (tokenarr[i++])
	{
		len++;
	}

	for (i = len - 1; i >= 0; i--)
		free(tokenarr[i]);

	free(tokenarr);
}

/**
 * _strdup - creates a copy of string allocated in heap
 * @str: string to be allocated
 *
 * Return: address of newly allocated string
 */

char *_strdup(char *str)
{
	int i = 0;
	int len = _strlen(str);

	char *copystr = malloc(sizeof(char) * (len + 1));

	if (copystr == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		copystr[i] = str[i];

	return (copystr);
}

/**
 * _realloc - reallocates memory
 * @ptr: ptr to memory to be allocated
 * @o_size: size of memory before allocation
 * @n_size: desired size of memory after allocation
 *
 * Return: address of reallocated memory
 */

void *_realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	void *mem;
	char *copy, *temp;
	unsigned int i;

	if (n_size == o_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(n_size);
		if (mem == NULL)
			return (NULL);
		return (mem);
	}

	if (n_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	copy = ptr;
	mem = malloc(sizeof(*copy) * n_size);

	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	temp = mem;

	for (i = 0; i < o_size && i < n_size; i++)
		temp[i] = *copy++;

	free(ptr);
	return (mem);
}
