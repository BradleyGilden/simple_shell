#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

#define wexitstat(status) (((status) >> 8) & 0xff)
typedef unsigned int usint;

extern char **environ;

/**
 * struct myglob - struct of global variables
 * @lineptr: string containing command line args
 * @copy: copy of string containing command line args
 * @tokens: tokenized 2d array of command line arguments
 * @es: error status of program
 * @ln: line number
 * @av: executable name
 */

typedef struct myglob
{
	char *lineptr;
	char *copy;
	char **tokens;
	int es;
	int ln;
	char *av;
} myglob_t;

/*digit handling*/
int count_digits(int num);
void to_string(int num, char *str);
int _atoi(char *s);
int _isdigit(char *str);
int tcnt(char **tok);

/*String Handling Functions*/
int _strlen(char *str);
char *str_cpy(char *dest, char *src);
int _strncmp(const char *str1, const char *str2, size_t len);
char *_strcat(char *dest, char *source);
int _strcmp(char *s1, char *s2);

/*Custom Functions*/
char **splitstr(char *line, char *linecopy);
void exec(char *cmd, myglob_t *glob);
void my_getline(char *av);
void non_interactive_mode(char *av);
char *_getenv(char *path);
char *find_path(char *cmd);
int check_path(char *cmd);
void forking(myglob_t *glob);
void display_prompt(void);
void w_out(char *message);

/*Built In Functions*/
int ch_builtin(myglob_t *glob);
void _printenv(void);
void exit_args(myglob_t *glob);
void echo_args(char **tok, int *es);

/*Memory management*/
void free_tokens(char **tokenarr);
void free_alloced_mem_on_exit(myglob_t *glob);
char *_strdup(char *str);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*Error Handling*/
void malloc_checkptr(char *s);
void malloc_checkdptr(char **s);
void getret(myglob_t *glob, ssize_t ret);
void write_cmd_err(myglob_t *glob);
void write_exec_err(myglob_t *glob);
void write_exec_err2(myglob_t *glob);
void forkerr(myglob_t *glob);

void handle_sigint(int __attribute__((unused))sig);
int letter_ch(char s[], const char *part);
char *str_tok(char str[], const char *part);

#endif /*_MAIN_H_*/
