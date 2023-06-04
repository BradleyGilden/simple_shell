# SASH - Simple Adolescent Shell

The purpose of this shell was to build a Unix shell similar to the `sh` shell from scratch. For help, seek [man_sash](man_sash)

## Navigation

* [File Descriptions](#file-descriptions)
* [Limied functions used](#list-of-limited-builtin-c-functions-used)
* [Using the shell](#using-the-shell)
* [Non-Interactive mode](#non-interactive-mode)

## File Descriptions

* [AUTHORS](AUTHORS) - The project authors' details
* [sash.h](sash.h) - Project header file
* [sash.c](sash.c) - The projects main file
* [getenv.c](getenv.c) - a custom getemv function
* [errhandler.c](errhandler.c) - Handles output errors
* [errhandler2.c](errhandler2.c) - Handles output errors
* [ctrloop.c](ctrloop.c) - The main shell loop that controls all processes
* [init_fork.c](init_fork.c) - Handles splitting child process from parent in order to execute commands
* [execute.c](execute.c) - Calls the `execve()` function to execute commands
* [pathfinder.c](pathfinder.c) - Detects if commands are in the systems PATH
* [tokenizer.c](tokenizer.c) - Tokenizes command line entered in order to be processed by execve()
* [memanager.c](memanager.c) - Handles all memory allocation and freeing
* [builtins.c](builtins.c) - Handles all builtin functions implemented
* [numhandler.c](numhandler.c) - Handles all digit conversions e.g int to string
* [strlib.c](strlib.c) - implementation of string handling functions like strlen() and strncmp()
* [sash](sash) - the shell executable

## List of limited builtin C functions used:

* isatty()
* write()
* access()
* getline()
* fflush()
* fork()
* wait()
* _exit()
* exit()
* stat()
* getpid()
* free()
* malloc()

<br>

# Using the Shell

## Non-Interactive Mode

In order to execute the shell in non interactive mode use this format: echo "[command]" | ./sash <br>
For example:
```
$ echo "ls" | ./sash
AUTHORS    builtins.c  errhandler.c   execute.c  init_fork.c  memanager.c   pathfinder.c  sash.c  strlib.c
README.md  ctrloop.c   errhandler2.c  getenv.c   man_sash     numhandler.c  sash          sash.h  tokenizer.c

```

## Interactive Mode

In order to execute shell in interactive mode simply enter `./sash`

For Example:
```
$ ./sash
✔ <0> $ ls
AUTHORS    builtins.c  errhandler.c   execute.c  init_fork.c  memanager.c   pathfinder.c  sash.c  strlib.c
README.md  ctrloop.c   errhandler2.c  getenv.c   man_sash     numhandler.c  sash          sash.h  tokenizer.c

✔ <0> $ echo "Hello World"
Hello World

✔ <0> $ 
```
note the format of the prompt: error-symbol <exit status\> $ 

## PATH

Note that the shell accepts the full directory in path of a function and also accepts the general alias of that path

```
✔ <0> $ /bin/echo "Hey Developer!"
Hey Developer!

✔ <0> $ echo "Bye Developer!"
Bye Developer!
```

## Command arguments

Because the commands entered are tokenized, the shell can also handle command arguments

```
✔ <0> $ ls -al
total 112
drwxr-xr-x 3 nightlock nightlock  4096 Jun  4 13:11 .
drwxr-xr-x 4 nightlock nightlock  4096 Jun  4 12:02 ..
drwxr-xr-x 9 nightlock nightlock  4096 Jun  4 13:12 .git
-rw-r--r-- 1 nightlock nightlock   249 Jun  4 12:02 AUTHORS
-rw-r--r-- 1 nightlock nightlock  2937 Jun  4 14:08 README.md
-rw-r--r-- 1 nightlock nightlock  2667 Jun  4 12:33 builtins.c
-rw-r--r-- 1 nightlock nightlock  1558 Jun  4 13:07 ctrloop.c
-rw-r--r-- 1 nightlock nightlock  1977 Jun  4 12:33 errhandler.c
-rw-r--r-- 1 nightlock nightlock   672 Jun  4 12:34 errhandler2.c
-rw-r--r-- 1 nightlock nightlock   414 Jun  4 12:34 execute.c
-rw-r--r-- 1 nightlock nightlock  1721 Jun  4 12:34 getenv.c
-rw-r--r-- 1 nightlock nightlock   993 Jun  4 12:34 init_fork.c
-rw-r--r-- 1 nightlock nightlock  4134 Jun  4 12:49 man_sash
-rw-r--r-- 1 nightlock nightlock  1855 Jun  4 12:35 memanager.c
-rw-r--r-- 1 nightlock nightlock  2110 Jun  4 12:35 numhandler.c
-rw-r--r-- 1 nightlock nightlock  1972 Jun  4 12:35 pathfinder.c
-rwxr-xr-x 1 nightlock nightlock 27520 Jun  4 13:11 sash
-rw-r--r-- 1 nightlock nightlock   559 Jun  4 13:11 sash.c
-rw-r--r-- 1 nightlock nightlock  2241 Jun  4 12:57 sash.h
-rw-r--r-- 1 nightlock nightlock  2206 Jun  4 12:36 strlib.c
-rw-r--r-- 1 nightlock nightlock  1006 Jun  4 12:36 tokenizer.c
```

## EOF and Signals

When sash detects EOF (^D), it exits the shell. When the signal SIGINT (^C) is emitted it cancels the current command 

```
✔ <0> $ rm -rf simple_shell^C
✔ <0> $ ^C
✔ <0> $ ^C
✔ <0> $                                     # ^D is entered here
$
```

## Builtins

* ## exit with args & echo with args
  
  You are able to forcefully exit with custom status using exit [value].
  Displaying exit status is also possible with echo $? and to display current process ID use: echo $$
  
  ```
  ✔ <0> $ echo hey
  hey

  ✔ <0> $ lsdjf
  ./sash: 2: lsdjf: not found

  ✖ <127> $ echo $?
  127

  ✔ <0> $ /bin
  ./sash: 2: /bin: Permission denied

  ✖ <126> $ echo $?
  126

  ✔ <0> $ echo $$
  11801

  ✔ <0> $ exit 22
  $ echo $?
  22
  
  ```
  note: symbol changes when there is an error and exit will work even without arguments

* ## env
  
  env is a custom builtin command that emulates the printenv command by printing the environment list line by line
  
  ```
  ✔ <0> $ env
  USER=nightlock
  WT_PROFILE_ID={07b52e3e-de2c-5db4-bd2d-ba144ed6c273}
  SHLVL=2
  HOME=/home/nightlock
  OLDPWD=/home/nightlock/workspace/C/simple_shell
  WSL_DISTRO_NAME=Ubuntu-20.04
  WAYLAND_DISPLAY=wayland-0
  LOGNAME=nightlock
  PULSE_SERVER=unix:/mnt/wslg/PulseServer
  WSL_INTEROP=/run/WSL/60_interop
  NAME=Code
  _=/home/nightlock/workspace/C/simple_shell/./sash
  TERM=xterm-256color
  PATH=/home/nightlock/.vscode-server/bin/b3e4e68a0bc097f0ae7907b217c1119af9e03435/bin/remote-cli:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files/Eclipse Adoptium/jdk-17.0.3.7-hotspot/bin:/mnt/c/Program Files/Common Files/Oracle/Java/javapath:/mnt/c/Program Files (x86)/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/Microsoft SQL Server/150/Tools/Binn/:/mnt/c/sqlite3:/mnt/c/Program Files/Java/jdk-18.0.1.1/bin:/mnt/c/Program Files/CMake/bin:/mnt/c/Program Files/Git/cmd:/mnt/c/Users/Student/scoop/shims:/mnt/c/Users/Student/AppData/Local/Microsoft/WindowsApps:/mnt/c/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin:/mnt/c/Program Files (x86)/Brackets/:/mnt/c/Users/Student/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/Student/Downloads/opencv/build/x64/vc15/bin:/mnt/c/Users/Student/AppData/Local/Programs/oh-my-posh/bin
  XDG_RUNTIME_DIR=/mnt/wslg/runtime-dir
  WT_SESSION=d9b16287-078d-4f4e-8db5-8e9eed7c2b42
  DISPLAY=172.19.32.1:0.0
  LANG=C.UTF-8
  SHELL=/usr/bin/zsh
  PWD=/home/nightlock/workspace/C/simple_shell
  HOSTTYPE=x86_64
  WSL2_GUI_APPS_ENABLED=1
  WSLENV=ELECTRON_RUN_AS_NODE/w:WT_SESSION::WT_PROFILE_ID
  
  ZSH=/home/nightlock/.oh-my-zsh
  PAGER=less
  LESS=-R
  LSCOLORS=Gxfxcxdxbxegedabagacad
  LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
  _P9K_SSH_TTY=/dev/pts/5
  P9K_TTY=old
  _P9K_TTY=/dev/pts/5
  TERM_PROGRAM=vscode
  TERM_PROGRAM_VERSION=1.78.2
  COLORTERM=truecolor
  GIT_ASKPASS=/home/nightlock/.vscode-server/bin/b3e4e68a0bc097f0ae7907b217c1119af9e03435/extensions/git/dist/askpass.sh
  VSCODE_GIT_ASKPASS_NODE=/home/nightlock/.vscode-server/bin/b3e4e68a0bc097f0ae7907b217c1119af9e03435/node
  VSCODE_GIT_ASKPASS_EXTRA_ARGS=
  VSCODE_GIT_ASKPASS_MAIN=/home/nightlock/.vscode-server/bin/b3e4e68a0bc097f0ae7907b217c1119af9e03435/extensions/git/dist/askpass-main.js
  VSCODE_GIT_IPC_HANDLE=/mnt/wslg/runtime-dir/vscode-git-3688587ea1.sock
  VSCODE_IPC_HOOK_CLI=/mnt/wslg/runtime-dir/vscode-ipc-4482a172-aec2-4559-abc1-a5a3e0a15539.sock
  VSCODE_INJECTION=1
  ZDOTDIR=/home/nightlock
  USER_ZDOTDIR=/home/nightlock
  P9K_SSH=0
  ```
