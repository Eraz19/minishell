# POSIX COMPLIANCE

This program targets the *POSIX IEEE Std 1003.1-2024 issue 8* specification provided by *The Open Group*.
However, this program is actually meant to be submitted as a *42 Paris School* project.
Therefore, fully *POSIX* compliance can **NOT** be achieved yet, principally due to the project *functions whitelist*, and the time deadline.
A future version of this program will make it fully *POSIX* compliant.

This documentation explains all the behaviours which are not compliants or not explicitly specified by the targeted specification:
- [Not implemented yet](#not-implemented-yet)
- [Limitations due to the *42 school functions whitelist*](#limitations-due-to-the-42-school-functions-whitelist)
- [Unspecified behaviours implementation](#unspecified-behaviours-implementations)
- [Undefined behaviours implementation](#undefined-behaviours)
- [Implementation-specific extensions](#implementation-specific-extensions)

---

## NOT IMPLEMENTED YET

This program is actually meant to be submitted as a *42 Paris School* project.
Therefore, some *POSIX* features can **NOT** be achieved in the project given time frame.
The following *POSIX* requirements will be implemented in a future version of this program.

- `options`:
	- `-b` (see Limitations due to the *42 school functions whitelist* -> *builtins* -> `jobs`)
	- `-m` (see Limitations due to the *42 school functions whitelist* -> *builtins* -> `jobs`)
	- `-u`
	- `-v`
	- `-o vi`
- `builtins`:
	- `bg` (see Limitations due to the *42 school functions whitelist* -> *builtins* -> `jobs`)
	- `command`
	- `fc`
	- `fg` (see Limitations due to the *42 school functions whitelist* -> *builtins* -> `jobs`)
	- `getopts`
	- `hash`
	- `jobs` (see Limitations due to the *42 school functions whitelist* -> *builtins* -> `jobs`)
	- `kill`
	- `read`
	- `type`
	- `ulimit`
	- `umask`
- *expansions*:
	- `arithmetic expansion` (see Limitations due to the *42 school functions whitelist* -> *expansions*)
	- `regex matching` (see Limitations due to the *42 school functions whitelist* -> *expansions*)

---

## LIMITATIONS DUE TO THE 42 SCHOOL FUNCTIONS WHITELIST

This program is actually meant to be submitted as a *42 Paris School* project.
Therefore, fully *POSIX* compliance of the following features can **NOT** be achieved due to the project *functions whitelist*.
However, a future version of this program will make it fully *POSIX* compliant.

- *Locale handling*:
	- As locale-management functions are forbidden, locale-dependent collation and character classification can't be achieved by this program; therefore, approximations with byte/ASCII-like semantics are used.
- Workarounds and/or *asm stubs* have been done to emulate the following functions which are not allowed by the official 42 subject:
	- `getpid()` -> `ft_getpid()`: get current process id for `$$` initialization:
		- `macOS` / ARM: asm stub.
		- `macOS` / x86: asm stub.
		- `linux`/ all: workaround via `/proc/self/status`.
		- `freeBSD` / all (all archs): workaround via `/proc/curproc/status` / `/proc/self/status`.
	- `getppid()` -> `ft_getppid()`: get parent process id for `$PPID` initialization:
		- `macOS` / ARM: asm stub.
		- `macOS` / x86: asm stub.
		- `linux`/ all: workaround via `/proc/self/status`.
		- `freeBSD` / all (all archs): workaround via `/proc/curproc/status` / `/proc/self/status`.
	- `fcntl()` -> `ioctl()`: set `stdin` to blocking mode for `stdin` management:
		- all OS and archs: via `ioctl()` (non-*POSIX* function) instead of `fcntl()`.
	- **TODO** `ft_getuid()`, `ft_geteuid()`, `ft_getgid()` and `ft_getegid()` to check `ENV` processing conditions.
	- ⚠️ as `OpenBSD` sends `SIGABRT` when `syscalls` are sent from unauthorized memory addresses, this features are not supported on this *Operating System*.
- *redirections*:
	- as `fcntl()` is forbidden, we check whether the rhs fd of `>&` / `<&` is open, but we do not check whether it is open respectively for writing or reading. This is still *POSIX*-compliant because *POSIX* says that a redirection error "may" result in that case.
	- as `fcntl()` is forbidden, we cannot allocate redirection backup fds atomically with `F_DUPFD`. We use `fstat()` + `dup2()` instead. This is considered safe enough for this program because it is single-threaded and its signal handlers do not open file descriptors.
	- as `fcntl()` is forbidden, backup fds cannot be marked as `FD_CLOEXEC`; therefore, whenever a child is forked to execute a command, the shell explicitly closes each tracked backup fd before calling `execve()` (best effort).
	- as `sysconf()` / `getrlimit()` are forbidden, we cannot query the actual file descriptor limit of the host process. *POSIX* only requires shell redirections to support user file descriptors 0 through 9. By default, this program uses 0..128 as its user fd range and reserves 129..256 for internal redirection backups. If the backup range is exhausted or unsupported by the host system, the redirection fails with a redirection error. A MAX_COMPAT build option can restrict the layout to 0..9 for user fds and 10..19 for backup fds, which is a more conservative *POSIX*-minimum layout but still does not guarantee that backup fds are available.
- *expansions*:
	- as `fn_match()` is forbidden, *regex matching* is not implemented.
	- as `libmath` is forbidden, *arithmetic expansion* is not implemented.
- *child processes*:
	- as `_exit()` is forbidden, child processes use `exit()`, which may flush inherited standard *I/O buffers* and run inherited *exit handlers*.
- `close()`:
	- as `posix_close()` and `POSIX_CLOSE_RESTART` are forbidden, `posix_close_if_open()` retries `close()` on `EINTR` and `EINPROGRESS` until the fd is either closed or already invalid; any other failure makes the fd tracker state non-recoverable (more details in `srcs/0_posix_helpers/posix_close_if_open.c`).
- *builtins*:
	- `jobs`, `fg`, `bg`:
		- as `setpgid()` / `tcsetpgrp()` / `getpgrp()` / `setsid()` are forbidden, `jobs`, `fg` and `bg` are not implemented.
	- `trap`:
		- as `str2sig()`, `sig2str()`, and `sysconf()` are forbidden, the shell cannot reliably support every implementation-defined signal provided by the host; therefore, signal names are resolved through a handwritten compile-time table, guarded by the macros available in `<signal.h>`, and unsupported implementation-defined signals are reported as invalid trap conditions.
- *options*:
	- `-b`: not implemented (see `builtins` -> `jobs`).
	- `-m`: partially implemented (see `builtins` -> `jobs`).

---

## UNSPECIFIED BEHAVIOURS IMPLEMENTATIONS

When an *unspecified behaviours* is triggered, this program prints a *warning* on `stderr`.
This *warning* explicitly quotes the *POSIX* section which defines it as *unspecified* and explains what behaviour this program implements for this specific case.
However, a future version of this program may only print such a warning when it is invoked with a specific custom *option*.

> ⚠️ Search for `print_unspecified_behaviour()` usage to find non-documented *unspecified behaviours*.

- `ENV`:
	- if `parameter expansion` of `ENV` value does'nt expand on an *absolute path*, no processing of the `ENV` file is done.
	- `ENV` file is processed even if the file can be written by any user other than the user identified by the real (and effective) user ID of the shell process. A future version of this program may implement a different behaviour in this case.
	- if first line of `ENV` file is a *shebang* (`#!`), shell treats it as a normal *comment* and ignores it.
- *options*:
	- `i` and `c` are printed in `$-` expansion.
	- `-o nolog` has no effect.
- *command search*:
	- *utilities*: No special treatment is done for "*unspecified command names*" so it can resolve to a *function* or an *external command*.
	- step 3 (apply *redirections*) and step 4 (expand and apply *variable assignments*) are always done in this same order.
- *functions*:
	- *assignments* persist after execution.
- *errors*:
	- *shell* does **NOT** exist on *command not found* error when it is not interactive.
- *redirections*:
	- *io location* are supported: they must expand to a valid *file descriptor*.
	- *heredoc*:
		- bodies are stored as a `t_string` inside the corresponding `AST` node.
		- errors are **NOT** treated as *redirection errors*, but a diagnostic is printed.
- *expansions*:
	- `$@` / `$*`: always expand as in a *field splitting* context:
		- `$@` / `$*` / `"$@"`: 1 field per parameter, first field joined with previous one and last field joined with next one.
		- `"$*"`: 1 field joined by first `IFS` character (` ` if *unset*, none if *set but null*).
- *command substitutions*:
	- closing `)` must not be inside an `alias`.
	- unignored `traps` are reset to default even if the `command substitution` only contains a `trap` command (see *builtins* -> `trap` bellow).
- *builtins*:
	- all builtins are conform to `Utility Syntax Guidelines` unless the targeted *specification* specifies that it doesn't.
	- `set`:
		- `-o` prints the current settings of the options in the same format as `+o`
	- `trap`:
		- `SIGTTIN`, `SIGTTOU` and `SIGTSTP` are always ignored in *interactive* shell (`-i`), even if `-m` is not active.
		- `SIGKILL` and `SIGSTOP` are not supported at all because they have *POSIX* *undefined behaviour* with `trap`.
		- when shell is *interactive* (`-i`), `trap` actions (`reset` or `catch`) are allowed on signals which were *ignored on entry*.
		- `EXIT / 0` traps are not processed when shell exists because of a `signal` for which `trap` action is `default`.
		- Like `bash`, *subshells* always reset *unignored traps* on entry. While no *command* including `trap` with at least one *operand* has been executed since entering the *subshell*, `trap` and `trap -p [condition...]` print *traps* as they were set immediately before entering the *subshell*. This remains true in `bash` and `minishell` even when `trap -p` is given one or more *condition operands* (the targeted *specification* is not precise about this specific case).
		- Unlike `bash`, and in strict conformance with targeted *specification* wording, `trap -p condition...` is treated as a `trap` command with at least one *operand*. Therefore, after such a command has been executed in a *subshell*, the parent *trap* snapshot is no longer available.
	- `return`:
		- if `n` is is not an unsigned decimal integer: returns `$?` value
		- if `n` is greater than 255: returns `n % 256`
	- `shift`:
		- if `n` invalid or is greater than `$#`: *special builtin error*
	- `break`, `continue`, `return`:
		- ⚠️ **TODO**: choose a behaviour for `If there is no enclosing loop, the behavior is unspecified.`
- `exit`:
	- ⚠️ **TODO**: cf `srcs/builtins/exit.c`
- *case pattern* using `$@` or `$*`:
	- if *expansion* produces 0 *field*, *pattern* is skipped (equivalent to a *pattern* which doesn't match the *case word*).
	- if *expansion* produces more than one *field*, each *field* is treated as a separate *pattern* to be matched against the *case word*.

---

## UNDEFINED BEHAVIOURS

For trolling purpose, undefined behaviours always print the *Xavier Niel* face on `stderr` in an *ASCII art* style.
However, a future version of this program may only print it when it is invoked with a specific custom *option*.

*Undefined behviours* don't make the *shell* exit by default
However, a future version of this program may exit if `-e` is active and an *undefined behaviour* is triggered.

> ⚠️ Search for `undefined_behaviour()` usage to find non-documented *undefined behaviours*.

- ⚠️ **TODO**

---

## IMPLEMENTATION-SPECIFIC EXTENSIONS

All of the extensions implemented by this program are fully *POSIX*-compliants.
This means all of them are compliants with the targeted *specification*.
These behaviours are implemented to fullfil *POSIX* missing specifications which may cause this program to *infinite loop* or *crash*.
Therefore, the **only** purpose of these additional features are to avoid the user losing control of the *shell*.

- When a *parameter expansion* which must produce exactly one *field* produces zero or more than one *field*, unless this documentation explicitly specifies another behaviour (as for `case` for example), they are merged into a single one using the first character of `IFS` (or ` ` if `IFS` is not set).
- Like `bash`, this program exits after 10 consecutive `EOF` to prevent *infinite loops*.
