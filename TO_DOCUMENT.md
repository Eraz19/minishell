# TO DOCUMENT

## POSIX limitations due to 42 functions whitelist

- Workarounds and/or asm stubs have been done to emulate the following functions which are not allowed by the official 42 subject:
	- `getpid()` -> `ft_getpid()`: get current process id for `$$` initialization:
		- `macOS` / ARM: asm stub
		- `macOS` / x86: asm stub
		- `linux`/ all: workaround via `/proc/self/status`
		- `freeBSD` / all (all archs): workaround via `/proc/curproc/status` / `/proc/self/status`
	- `getppid()` -> `ft_getppid()`: get parent process id for `$PPID` initialization
		- `macOS` / ARM: asm stub
		- `macOS` / x86: asm stub
		- `linux`/ all: workaround via `/proc/self/status`
		- `freeBSD` / all (all archs): workaround via `/proc/curproc/status` / `/proc/self/status`
	- `fcntl()` -> `ioctl()`: set `stdin` to blocking mode for `stdin` management
		- all OS and archs: via `ioctl()` (non-POSIX function) instead of `fcntl()`
- ⚠️ as `OpenBSD` sends `SIGABRT` when `syscalls` are sent from unauthorized memory addresses, this `shell` is not fully POSIX compliant on this Operating System. A next version of this program may use all the real `libc` functions to enable full POSIX compliance.
- `heredoc`:
	- as `mkdir()` and `mktmp()` is forbidden, we can't properly create a tmp file, so we just iterate over an 0-INT_MAX file_name suffix to find an available filename to create directly in `tmp/`
	- as `lseek()` is forbidden, we can't keep the `fd` open, so we `open()`/`close()` the tmp file several times to re-roll it
- `redirections`:
	- as `fcntl()` is forbidden, we check whether the rhs fd of `>&` / `<&` is open, but we do not check whether it is open respectively for writing or reading. This is still POSIX-compliant because POSIX says that a redirection error "may" result in that case.
	- as `fcntl()` is forbidden, we cannot allocate redirection backup fds atomically with `F_DUPFD`. We use `fstat()` + `dup2()` instead. This is considered safe enough for `minishell` because it is single-threaded and its signal handlers do not open file descriptors.
	- as `sysconf()` / `getrlimit()` are forbidden, we cannot query the actual file descriptor limit of the host process. POSIX only requires shell redirections to support user file descriptors 0 through 9. By default, `minishell` uses 0..128 as its user fd range and reserves 129..256 for internal redirection backups. If the backup range is exhausted or unsupported by the host system, the redirection fails with a redirection error. A MAX_COMPAT build option can restrict the layout to 0..9 for user fds and 10..19 for backup fds, which is a more conservative POSIX-minimum layout but still does not guarantee that backup fds are available.
- `expander`:
	- as `fn_match()` is forbidden, regex matching is not implemented.
- `runner`:
	- `redirector-tracker`:
		- as `fcntl()` is forbidden, backup fds cannot be marked as `FD_CLOEXEC`; therefore, whenever a child is forked to execute a command, the shell explicitly closes each tracked backup fd before calling `execve()` (best effort).
	- `executor`:
		- as `_exit()` is forbidden, shell child processes use `exit()`, which may flush inherited standard I/O buffers and run inherited exit handlers.
- `async`:
	- `jobs`:
		- as `setpgid()` / `tcsetpgrp()` / `getpgrp()` / `setsid()` are forbidden, job-control background jobs and non-job-control background jobs are not implemented.
- `pattern matching`:
	- as locale-management functions are forbidden, pattern matching ignores locale-dependent collation and character classification; therefore, bracket ranges, equivalence classes, collating symbols, and character classes are only approximated with byte/ASCII-like semantics.

## POSIX UNSPECIFIED IMPLEMENTATIONS

⚠️ Search for `print_unspecified_behaviour()` usage
- `utilities`:
	- No special treatment is done for `unspecified command names` so it can resolve to a `function` or an `external command`
- `functions`:
	- `assignments` persist after execution
- `errors`:
	- shell exists on `command not found` error when shell is not interactive
- `redirections`:
	- `io location` are supported: must expand to a valid file descriptor
	- `word` expansion producing more than one field : we merge it with first `IFS` character (` ` if *unset*, none if *set but null*)
- `expansions`:
	- `$@` / `$*`: always expand as in a *field splitting* context:
		- `$@` / `$*` / `"$@"`: 1 field per parameter, first field joined with previous one and last field joined with next one
		- `"$*"`: 1 field joined by first `IFS` character (` ` if *unset*, none if *set but null*)
- ...

### `$@` / `$*` UNSPECIFIED CASES IMPLEMENTATIONS

**POSIX 2.5.2 Special Parameters**:
- `$@`					=> 1 field **per parameter**, join [first with before] + join [last with after]
- `$*` + unquoted		=> 1 field **per parameter**, join [first with before] + join [last with after]
- `$*` + quoted			=> **only** 1 field, joined with:
	- if `IFS` len > 0				=> `IFS[0]`
	- if `IFS` is *unset*			=> ` `
	- if `IFS` is *set but null*	=> *nothing*
- if no *field spillting*	=> UNSPECIFIED => **MINISHELL** => same behaviour as if field splitting was active

**MINISHELL**:
- `$@`:
	- `redirection filename`: merge fields with first `IFS` character
	- `case word`: 0 field => `""`
	- `case word`: n fields => merge fields with first `IFS` character
	- `case pattern`: 0 field => skip (match = false)
	- `case pattern`: n fields => match sur chaque field

**YASH (normal / -o posixlycorrect)**
- `$@`:
	- `redirection`: always merge fields in `filename`
	- `case`: always merge patterns

**BASH --posix**:
- `$@`:
	- `redirection`: always merge fields in `filename`
	- `case`: unquoted => merge fields
	- `case`: quoted => only keep first field

**BASH**:
- `$@`:
	- `redirection`: error "redirection ambigue"
	- `case`: unquoted => merge fields
	- `case`: quoted => only keep first field

**ZSH**:
- `$@`:
	- `redirection`: always redirect to one file per field
	- `case`: always merge patterns

---

## lr_machine.md

- Préciser que `ACTION` est complétée étape par étape avec un process et un payload différents pour :
	- `ERROR`: default
	- `SHIFT`: `action.payload` = `transition.to_lr_state_id`
	- `REDUCE`: `action.payload` = `lr_state[i].rule_state.rule_id` (only for `rules` with `pos` >= `rhs_len`)
	- `ACCEPT`: same as `REDUCE` but only if `rule.lhs` = `SYM_start` and for `SYM_EOF`

## What I learned

- Read, understand and implement an **industrial standard** (`POSIX`)
- Think, find and implement a suitable **architecture** for a large purpose program:
	- **deep modules** strategy: `scanner` (aka `lexer`) + `builder` (aka `parser`) + `runner` (aka `executor`)
	- **memory safety** flow: init, run, free
	- **error management**: handle various error types, printing and absorbing strategies
- Work as a **team** with `git` and `discord` (2 members):
	- **git branches**
	- **git issues**
	- **github actions** (`CI/CD`)
	- **discord hooks**
