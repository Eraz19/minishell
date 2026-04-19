# C Functions Reference

## I/O – File Descriptors

| Function | Signature | Description |
|----------|-----------|-------------|
| `open` | `int open(const char *pathname, int flags, ... /* mode_t mode */)` | Opens (or creates) a file and returns a file descriptor. flags: `O_RDONLY`, `O_WRONLY`, `O_RDWR`, `O_CREAT`, `O_TRUNC`, etc. |
| `read` | `ssize_t read(int fd, void *buf, size_t count)` | Reads up to `count` bytes from `fd` into `buf`. Returns the number of bytes actually read, 0 on EOF, -1 on error. |
| `close` | `int close(int fd)` | Closes the file descriptor `fd`, releasing the associated resource. |
| `write` | `ssize_t write(int fd, const void *buf, size_t count)` | Writes `count` bytes from `buf` to `fd`. Returns the number of bytes written, or -1 on error. |
| `dup` | `int dup(int oldfd)` | Duplicates `oldfd` using the lowest available file descriptor number. |
| `dup2` | `int dup2(int oldfd, int newfd)` | Duplicates `oldfd` as `newfd`, closing `newfd` first if necessary. |
| `pipe` | `int pipe(int pipefd[2])` | Creates a unidirectional data channel. `pipefd[0]` = read end, `pipefd[1]` = write end. |

---

## I/O – Directories

| Function | Signature | Description |
|----------|-----------|-------------|
| `opendir` | `DIR *opendir(const char *name)` | Opens the directory `name` and returns a pointer to a DIR stream. |
| `readdir` | `struct dirent *readdir(DIR *dirp)` | Returns a pointer to the next entry in the directory stream `dirp`. |
| `closedir` | `int closedir(DIR *dirp)` | Closes the directory stream `dirp` and frees associated resources. |

---

## I/O – Formatted Output

| Function | Signature | Description |
|----------|-----------|-------------|
| `printf` | `int printf(const char *format, ...)` | Writes formatted output to stdout. Returns the number of characters printed, or a negative value on error. |

---

## I/O – Readline (interactive input)

| Function | Signature | Description |
|----------|-----------|-------------|
| `readline` | `char *readline(const char *prompt)` | Displays `prompt`, then reads a line of input from the user (with line-editing). Returns a malloc'd string; the caller must `free()` it. Returns NULL on EOF. |
| `add_history` | `void add_history(const char *string)` | Adds `string` to the readline history list, enabling up-arrow recall. |
| `rl_clear_history` | `void rl_clear_history(void)` | Frees all entries currently stored in the readline history list. |
| `rl_on_new_line` | `void rl_on_new_line(void)` | Notifies readline that the cursor has moved to a new line (used for redisplay). |
| `rl_replace_line` | `void rl_replace_line(const char *text, int clear_undo)` | Replaces the current readline input buffer content with `text`. If `clear_undo` is non-zero, the undo list is also cleared. |
| `rl_redisplay` | `void rl_redisplay(void)` | Redraws the current readline prompt and input buffer on the terminal. |

---

## Memory

| Function | Signature | Description |
|----------|-----------|-------------|
| `malloc` | `void *malloc(size_t size)` | Allocates `size` bytes of uninitialized heap memory. Returns a pointer to the block, or NULL on failure. |
| `free` | `void free(void *ptr)` | Releases a block of heap memory previously allocated by `malloc`/`calloc`/`realloc`. Passing NULL is a no-op. |

---

## File System

| Function | Signature | Description |
|----------|-----------|-------------|
| `access` | `int access(const char *pathname, int mode)` | Checks whether the calling process can access `pathname`. mode: `F_OK` (existence), `R_OK`, `W_OK`, `X_OK`. Returns 0 on success, -1 on error. |
| `stat` | `int stat(const char *pathname, struct stat *statbuf)` | Retrieves metadata about `pathname` (size, permissions, timestamps…) into `statbuf`. Follows symbolic links. |
| `lstat` | `int lstat(const char *pathname, struct stat *statbuf)` | Like `stat()`, but if `pathname` is a symbolic link, returns info about the link itself rather than the file it points to. |
| `fstat` | `int fstat(int fd, struct stat *statbuf)` | Like `stat()`, but operates on an already-open file descriptor `fd`. |
| `unlink` | `int unlink(const char *pathname)` | Removes the filesystem directory entry for `pathname`. The file is deleted when its link count reaches zero and no process has it open. |
| `getcwd` | `char *getcwd(char *buf, size_t size)` | Copies the absolute path of the current working directory into `buf`. Returns `buf` on success, NULL on error. |
| `chdir` | `int chdir(const char *path)` | Changes the current working directory of the calling process to `path`. |

---

## Processes

| Function | Signature | Description |
|----------|-----------|-------------|
| `fork` | `pid_t fork(void)` | Creates a child process as a copy of the calling process. Returns 0 in the child, the child's PID in the parent, -1 on error. |
| `execve` | `int execve(const char *pathname, char *const argv[], char *const envp[])` | Replaces the current process image with the program at `pathname`. `argv[]` = argument list (NULL-terminated), `envp[]` = environment. Does not return on success. |
| `wait` | `pid_t wait(int *wstatus)` | Blocks until any child process terminates; stores its exit status in `wstatus`. Returns the PID of the terminated child, or -1 on error. |
| `waitpid` | `pid_t waitpid(pid_t pid, int *wstatus, int options)` | Waits for a specific child `pid` to change state. Pass `pid = -1` to wait for any child. options: `WNOHANG`, `WUNTRACED`, etc. |
| `wait3` | `pid_t wait3(int *wstatus, int options, struct rusage *rusage)` | Like `waitpid(-1, …)` but also fills `rusage` with the child's resource usage. |
| `wait4` | `pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)` | Like `waitpid()` but also fills `rusage` with the child's resource usage. |
| `exit` | `void exit(int status)` | Terminates the calling process with `status`, flushing stdio buffers and invoking functions registered with `atexit()`. |

---

## Signals

| Function | Signature | Description |
|----------|-----------|-------------|
| `signal` | `sighandler_t signal(int signum, sighandler_t handler)` | Installs `handler` for signal `signum`. Returns the previous handler. Note: prefer `sigaction()` for portable and robust signal handling. |
| `sigaction` | `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)` | Examines and/or changes the action taken on signal `signum`. Stores the previous action in `oldact` if non-NULL. |
| `sigemptyset` | `int sigemptyset(sigset_t *set)` | Initializes the signal set `set` to be empty (no signals included). |
| `sigaddset` | `int sigaddset(sigset_t *set, int signum)` | Adds signal `signum` to the signal set `set`. |
| `kill` | `int kill(pid_t pid, int sig)` | Sends signal `sig` to the process (or process group) identified by `pid`. `kill(pid, 0)` can be used to check whether a process exists. |

---

## Error Handling

| Function | Signature | Description |
|----------|-----------|-------------|
| `strerror` | `char *strerror(int errnum)` | Returns a pointer to a human-readable string describing the error code `errnum`. |
| `perror` | `void perror(const char *s)` | Prints `s` followed by `": "` and the description of the current `errno` to stderr. |

---

## Terminal / TTY Control

| Function | Signature | Description |
|----------|-----------|-------------|
| `isatty` | `int isatty(int fd)` | Returns 1 if `fd` refers to an open terminal (TTY) device, 0 otherwise. |
| `ttyname` | `char *ttyname(int fd)` | Returns the name of the terminal device associated with `fd` (e.g. `"/dev/pts/0"`). |
| `ttyslot` | `int ttyslot(void)` | Returns the index of the calling process's entry in the utmp file. |
| `ioctl` | `int ioctl(int fd, unsigned long request, ...)` | Performs device-specific control operations on `fd` (e.g., `TIOCGWINSZ` to get terminal window size). |
| `getenv` | `char *getenv(const char *name)` | Returns the value of the environment variable `name`, or NULL if not set. |
| `tcsetattr` | `int tcsetattr(int fd, int optional_actions, const struct termios *termios_p)` | Applies the terminal attributes in `termios_p` to the terminal `fd`. optional_actions: `TCSANOW` (immediately), `TCSADRAIN`, `TCSAFLUSH`. |
| `tcgetattr` | `int tcgetattr(int fd, struct termios *termios_p)` | Reads the current terminal attributes of `fd` into `termios_p`. |

---

## Terminfo / Low-level Terminal Capabilities

| Function | Signature | Description |
|----------|-----------|-------------|
| `tgetent` | `int tgetent(char *bp, const char *name)` | Loads the terminfo/termcap entry for terminal type `name` into buffer `bp`. Returns 1 on success, 0 if the terminal is not found, -1 on error. |
| `tgetflag` | `int tgetflag(const char *id)` | Returns 1 if the boolean terminfo capability `id` is set, 0 otherwise. |
| `tgetnum` | `int tgetnum(const char *id)` | Returns the numeric value of terminfo capability `id`, or -1 if not present. |
| `tgetstr` | `char *tgetstr(const char *id, char **area)` | Returns the string value of terminfo capability `id`, or NULL if absent. Advances `*area` past the stored string. |
| `tgoto` | `char *tgoto(const char *cap, int col, int row)` | Substitutes the cursor-position parameters `col` and `row` into the capability string `cap` and returns the resulting escape sequence. |
| `tputs` | `int tputs(const char *str, int affcnt, int (*putc)(int))` | Outputs the terminfo string `str` with proper padding applied. `affcnt` = number of lines affected; `putc` is the output function (e.g. `putchar`). |



1. Triple-Character Operators
<<- : Strip Here-Doc (Redirects text, removes leading tabs)

<<< : Here-String (Redirects a single string to stdin)

&>> : Append Both (Appends both stdout and stderr to a file)

2. Double-Character Operators
|| : Logical OR (Run next if previous fails)

&& : Logical AND (Run next if previous succeeds)

|& : Pipe Error (Pipe both stdout and stderr)

>> : Append Output (Add stdout to end of file)

<< : Here-Doc (Redirect multi-line text to stdin)

<& : Duplicate Input (Copy an input file descriptor)

>& : Duplicate Output (Copy an output file descriptor)

&> : Redirect Both (Stdout and stderr to file)

<> : Read/Write (Open file for both reading and writing)

>| : Force Overwrite (Overwrite even if noclobber is set)

;; : Case Terminator (Used in case statements)

3. Single-Character Operators
| : Pipe (Connect stdout of A to stdin of B)

& : Background (Run command without waiting)

; : Semicolon (Command separator)

< : Input Redirection (Read stdin from file)

> : Output Redirection (Write stdout to file)

( : Subshell Start (Open command group)

) : Subshell End (Close command group)

\n: Newline (Command separator/terminator)