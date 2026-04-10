/* ============================================================ */
/*                     I/O – File Descriptors                   */
/* ============================================================ */

// int open(const char *pathname, int flags, ... /* mode_t mode */);
//   Opens (or creates) a file and returns a file descriptor.
//   flags: O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC, etc.

// ssize_t read(int fd, void *buf, size_t count);
//   Reads up to `count` bytes from `fd` into `buf`.
//   Returns the number of bytes actually read, 0 on EOF, -1 on error.

// int close(int fd);
//   Closes the file descriptor `fd`, releasing the associated resource.

// ssize_t write(int fd, const void *buf, size_t count);
//   Writes `count` bytes from `buf` to `fd`.
//   Returns the number of bytes written, or -1 on error.

// int dup(int oldfd);
//   Duplicates `oldfd` using the lowest available file descriptor number.

// int dup2(int oldfd, int newfd);
//   Duplicates `oldfd` as `newfd`, closing `newfd` first if necessary.

// int pipe(int pipefd[2]);
//   Creates a unidirectional data channel.
//   pipefd[0] = read end, pipefd[1] = write end.

/* ============================================================ */
/*                     I/O – Directories                        */
/* ============================================================ */

// DIR *opendir(const char *name);
//   Opens the directory `name` and returns a pointer to a DIR stream.

// struct dirent *readdir(DIR *dirp);
//   Returns a pointer to the next entry in the directory stream `dirp`.

// int closedir(DIR *dirp);
//   Closes the directory stream `dirp` and frees associated resources.

/* ============================================================ */
/*                     I/O – Formatted Output                   */
/* ============================================================ */

// int printf(const char *format, ...);
//   Writes formatted output to stdout.
//   Returns the number of characters printed, or a negative value on error.

/* ============================================================ */
/*                     I/O – Readline (interactive input)       */
/* ============================================================ */

// char *readline(const char *prompt);
//   Displays `prompt`, then reads a line of input from the user (with line-editing).
//   Returns a malloc'd string; the caller must free() it. Returns NULL on EOF.

// void add_history(const char *string);
//   Adds `string` to the readline history list, enabling up-arrow recall.

// void rl_clear_history(void);
//   Frees all entries currently stored in the readline history list.

// void rl_on_new_line(void);
//   Notifies readline that the cursor has moved to a new line (used for redisplay).

// void rl_replace_line(const char *text, int clear_undo);
//   Replaces the current readline input buffer content with `text`.
//   If `clear_undo` is non-zero, the undo list is also cleared.

// void rl_redisplay(void);
//   Redraws the current readline prompt and input buffer on the terminal.

/* ============================================================ */
/*                        Memory                                */
/* ============================================================ */

// void *malloc(size_t size);
//   Allocates `size` bytes of uninitialized heap memory.
//   Returns a pointer to the block, or NULL on failure.

// void free(void *ptr);
//   Releases a block of heap memory previously allocated by malloc/calloc/realloc.
//   Passing NULL is a no-op.

/* ============================================================ */
/*                        File System                           */
/* ============================================================ */

// int access(const char *pathname, int mode);
//   Checks whether the calling process can access `pathname`.
//   mode: F_OK (existence), R_OK, W_OK, X_OK. Returns 0 on success, -1 on error.

// int stat(const char *pathname, struct stat *statbuf);
//   Retrieves metadata about `pathname` (size, permissions, timestamps…)
//   into `statbuf`. Follows symbolic links.

// int lstat(const char *pathname, struct stat *statbuf);
//   Like stat(), but if `pathname` is a symbolic link, returns info
//   about the link itself rather than the file it points to.

// int fstat(int fd, struct stat *statbuf);
//   Like stat(), but operates on an already-open file descriptor `fd`.

// int unlink(const char *pathname);
//   Removes the filesystem directory entry for `pathname`.
//   The file is deleted when its link count reaches zero and no process has it open.

// char *getcwd(char *buf, size_t size);
//   Copies the absolute path of the current working directory into `buf`.
//   Returns `buf` on success, NULL on error.

// int chdir(const char *path);
//   Changes the current working directory of the calling process to `path`.

/* ============================================================ */
/*                        Processes                             */
/* ============================================================ */

// pid_t fork(void);
//   Creates a child process as a copy of the calling process.
//   Returns 0 in the child, the child's PID in the parent, -1 on error.

// int execve(const char *pathname, char *const argv[], char *const envp[]);
//   Replaces the current process image with the program at `pathname`.
//   argv[] = argument list (NULL-terminated), envp[] = environment.
//   Does not return on success.

// pid_t wait(int *wstatus);
//   Blocks until any child process terminates; stores its exit status in `wstatus`.
//   Returns the PID of the terminated child, or -1 on error.

// pid_t waitpid(pid_t pid, int *wstatus, int options);
//   Waits for a specific child `pid` to change state.
//   Pass pid = -1 to wait for any child. options: WNOHANG, WUNTRACED, etc.

// pid_t wait3(int *wstatus, int options, struct rusage *rusage);
//   Like waitpid(-1, …) but also fills `rusage` with the child's resource usage.

// pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
//   Like waitpid() but also fills `rusage` with the child's resource usage.

// void exit(int status);
//   Terminates the calling process with `status`, flushing stdio buffers
//   and invoking functions registered with atexit().

/* ============================================================ */
/*                        Signals                               */
/* ============================================================ */

// sighandler_t signal(int signum, sighandler_t handler);
//   Installs `handler` for signal `signum`. Returns the previous handler.
//   Note: prefer sigaction() for portable and robust signal handling.

// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
//   Examines and/or changes the action taken on signal `signum`.
//   Stores the previous action in `oldact` if non-NULL.

// int sigemptyset(sigset_t *set);
//   Initializes the signal set `set` to be empty (no signals included).

// int sigaddset(sigset_t *set, int signum);
//   Adds signal `signum` to the signal set `set`.

// int kill(pid_t pid, int sig);
//   Sends signal `sig` to the process (or process group) identified by `pid`.
//   kill(pid, 0) can be used to check whether a process exists.

/* ============================================================ */
/*                     Error Handling                           */
/* ============================================================ */

// char *strerror(int errnum);
//   Returns a pointer to a human-readable string describing the error code `errnum`.

// void perror(const char *s);
//   Prints `s` followed by ": " and the description of the current errno to stderr.

/* ============================================================ */
/*              Terminal / TTY Control                          */
/* ============================================================ */

// int isatty(int fd);
//   Returns 1 if `fd` refers to an open terminal (TTY) device, 0 otherwise.

// char *ttyname(int fd);
//   Returns the name of the terminal device associated with `fd` (e.g. "/dev/pts/0").

// int ttyslot(void);
//   Returns the index of the calling process's entry in the utmp file.

// int ioctl(int fd, unsigned long request, ...);
//   Performs device-specific control operations on `fd`
//   (e.g., TIOCGWINSZ to get terminal window size).

// char *getenv(const char *name);
//   Returns the value of the environment variable `name`, or NULL if not set.

// int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
//   Applies the terminal attributes in `termios_p` to the terminal `fd`.
//   optional_actions: TCSANOW (immediately), TCSADRAIN, TCSAFLUSH.

// int tcgetattr(int fd, struct termios *termios_p);
//   Reads the current terminal attributes of `fd` into `termios_p`.

/* ============================================================ */
/*          Terminfo / Low-level Terminal Capabilities          */
/* ============================================================ */

// int tgetent(char *bp, const char *name);
//   Loads the terminfo/termcap entry for terminal type `name` into buffer `bp`.
//   Returns 1 on success, 0 if the terminal is not found, -1 on error.

// int tgetflag(const char *id);
//   Returns 1 if the boolean terminfo capability `id` is set, 0 otherwise.

// int tgetnum(const char *id);
//   Returns the numeric value of terminfo capability `id`, or -1 if not present.

// char *tgetstr(const char *id, char **area);
//   Returns the string value of terminfo capability `id`, or NULL if absent.
//   Advances `*area` past the stored string.

// char *tgoto(const char *cap, int col, int row);
//   Substitutes the cursor-position parameters `col` and `row` into the
//   capability string `cap` and returns the resulting escape sequence.

// int tputs(const char *str, int affcnt, int (*putc)(int));
//   Outputs the terminfo string `str` with proper padding applied.
//   `affcnt` = number of lines affected; `putc` is the output function (e.g. putchar).
