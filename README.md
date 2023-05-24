# hsh - Simple Shell

A simple UNIX command interpreter written as part of the low-level programming and algorithm track at ALX.

## Description

**hsh** is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

### Invocation
Usage: **hsh** [filename]

To invoke **hsh**, compile all `.c` files in the repository and run the resulting executable:

``` 
gcc *.c -o hsh
./hsh
```

**hsh** can be invoked both interactively and non-interactively. If **hsh** is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

If **hsh** is invoked with standard input connected to a terminal (determined by [isatty](https://linux.die.net/man/3/isatty)(3)), an *interactive* shell is opened. When executing interactively, **hsh** displays the prompt `$ ` when it is ready to read a command.

Alternatively, if command line arguments are supplied upon invocation, **hsh** treats the first argument as a file from which to read commands. The supplied file should contain one command per line. **hsh** runs each of the commands contained in the file in order before exiting.

### Environment
Upon invocation, **hsh** receives and copies the environment of the parent process in which it was executed. This environment is an array of *name-value* strings describing variables in the format *NAME=VALUE*. A few key environmental variables are:
* **HOME**
The home directory of the current user and the default directory argument for the **cd** builtin command.

* **PWD**
The current working directory as set by the **cd** command.

* **OLDPWD**
The previous working directory as set by the **cd** command.

* **PATH**
A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

### Command Execution
After receiving a command, **hsh** tokenizes it into words using `" "` as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command. **hsh** then proceeds with the following actions:
* If the first character of the command is neither a slash (`\`) nor dot (`.`), the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
* If the first character of the command is none of a slash (`\`), dot (`.`), nor builtin, **hsh** searches each element of the **PATH** environmental variable for a directory containing an executable file by that name.
* If the first character of the command is a slash (`\`) or dot (`.`) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

### Exit Status
**hsh** returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

If a command is not found, the return status is 127; if a command is found but is not executable, the return status is 126.

All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

### Signals
While running in interactive mode, **hsh** ignores the keyboard input `Ctrl+c`. Alternatively, an input of end-of-file (`Ctrl+d`) will exit the program. 

### Variable Replacement
**hsh** interprets the `$` character for variable replacement.
* `$ENV_VARIABLE`
  * `ENV_VARIABLE` is substituted with its value.

* `$?`
  * `?` is substitued with the return value of the last program executed.

* `$$`
  * The second `$` is substitued with the current process ID.

### Comments
**hsh** ignores all words and characters preceeded by a `#` character on a line.

### Operators
**hsh** specially interprets the following operator characters:
* `;` - Command separator
  * Commands separated by a `;` are executed sequentially.

* `&&` - AND logical operator
  * `command1 && command2`: `command2` is executed if, and only if, `command1` returns an exit status of zero.

* `||` - OR logical operator
  * `command1 || command2`: `command2` is executed if, and only if, `command1` returns a non-zero exit status.

The operators `&&` and `||` have equal precedence, followed by `;`.

### hsh Builtin Commands
* **cd**
  * Usage: `cd [DIRECTORY]`
  * Changes the current directory of the process to `DIRECTORY`.
  * If no argument is given, the command is interpreted as `cd $HOME`.
  * If the argument `-` is given, the command is interpreted as `cd $OLDPWD` and the pathname of the new working directory is printed to standad output.
  * If the argument, `--` is given, the command is interpreted as `cd $OLDPWD` but the pathname of the new working directory is not printed.
  * The environment variables `PWD` and `OLDPWD` are updated after a change of directory.

* **alias**
  * Usage: `alias [NAME[='VALUE'] ...]`
  * Handles aliases.
  * `alias`: Prints a list of all aliases, one per line, in the form `NAME='VALUE'`.
  * `alias NAME [NAME2 ...]`: Prints the aliases `NAME`, `NAME2`, etc. one per line, in the form `NAME='VALUE'`.
  * `alias NAME='VALUE' [...]`: Defines an alias for each `NAME` whose `VALUE` is given. If `name` is already an alias, its value is replaced with `VALUE`.

* **exit**
  * Usage: `exit [STATUS]`
  * Exits the shell.
  * The `STATUS` argument is the integer used to exit the shell.
  * If no argument is given, the command is interpreted as `exit 0`.

* **env**
  * Usage: `env`
  * Prints the current environment.

* **setenv**
  * Usage: `setenv [VARIABLE] [VALUE]`
  * Initializes a new environment variable, or modifies an existing one.
  * Upon failure, prints a message to `stderr`.

* **unsetenv**
  * Usage: `unsetenv [VARIABLE]`
  * Removes an environmental variable.
  * Upon failure, prints a message to `stderr`.

## Authors
* Bradley Gilden - ALX student
* Lebohang KevCare Mokobane - ALX student


## Acknowledgements

This project was written as part of the curriculum for ALX. 


