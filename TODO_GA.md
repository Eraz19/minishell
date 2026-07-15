# WIP

⚠️ Tous les calls à l'`expander`:
- ne pas update `exit_status` s'il vaut `-1` !
- Ça écraserait le status de la dernière commande substitution !
- ===> Chaque expansion:
	- set `tmp_exit_status = -1`
	- récupérer le `tmp_exit_status` de l'expander
	- update le vrai `exit_status` uniquement si `tmp_exit_status >= 0`

- ⚠️ `exit_status`:
	- remove some `exit_status = -1` to avoid losing expansion / redirection status ?

🧪 Tester expansions qui produisent 0 / 1 / plusieurs fields:
- `redirections`
- `heredoc body`
- `assignments`
- `command name`

🧪 Tester les exit status des command substitutions dans:
- `assignments`
- `redirections`
- `words`
- `case` / `for` / `loop` components...
- `functions`
- ...

## LAST EXPANDED COMMAND SUBSTITUTION STATUS

```bash
A=$(true)
echo "should be 0 => $?"
#
A=$(false)
echo "should be 1 => $?"
#
cat << EOF
$(true)
EOF
echo "should be 0 => $?"
#
cat << EOF
$(false)
EOF
echo "should be 0 => $?"
#
<< EOF
$(true)
EOF
echo "should be 0 => $?"
#
<< EOF
$(false)
EOF
echo "should be 1 => $?"
```

⚠️ `echo` is removed from known builtin list to test
💡 Les erreurs dépendent de l'opération qui a échouée:
===> donc une `ERR_EXPANSION` ne peut jamais être requalifiée en `ERR_REDIRECTION`, `ERR_ASSIGNMENT`, etc.

- `builder`:
	- handle `command substitution search`
- `runner-executor`:
	- ⚠️ `exec` specific flow
	- ⚠️ `command` specific flow
	- `execve fallback`: don't free `lr_machine` to avoid recomputing tables
- `posix_read_all()`

# ALEXANDER

- ⚠️ docs:
	- Replace `Same contract as @ref ...` par les erreurs retournées (insup à utiliser)
- 🚧 `expander`:
	- ✅ `expansion_merge()` implemented by GA
	- ⚠️ use `int exit_status_priorize(int prev, int new)` (`utils.h`):
		- `new` doit être set à `-1`
- ⚠️ `pattern matching`: wip
- ⚠️ `expander`:
	- expand combos:
		- `str` -> `str`
		- `token` -> `str`
		- `token` -> `expansion`
	- return last `command substitution` status
- ⚠️ `heredoc`:
	- use `t_string` instead of file
	- stack delim inside `parser`
- `token`: keep `history_list_index` in `t_token_index` ?
```bash
VAR=value          => status 0
VAR=$(true)        => status 0
VAR=$(false)       => status 1
VAR=${bad syntax}  => ERR_POSIX_EXPANSION
```
- ⚠️ **all**:
	- replace all `ERR_INDEX_OUT_OF_BOND`, etc by `error_print()` + `ERR_INTERNAL`
- 🤔 move `heredoc.h` into `srcs/scanner/` ?
- `echo` (and other builtins):
	- Minimal 42 implementation or POSIX implementation ?
- 🚧 `shell`:
	- `shell_init_subshell()`: (only missing traps / signal handling)
- ✅ `runner_set_stdin_to_blocking()`:
	- now called in `readline_()`
- ✅ `hashmap`:
	- rename `hashmap_get()` as `hashmap_get_const()` and create `hashmap_get()`
	- `functions` module need to modify values in place (avoid copying whole `ast` at each function execution)
- ✅ `ast`:
	- now fully owned (massive refactor)
- ✅ `redirector`:
	- refactored for `ast` updates
- ✅ `executor`:
	- refactored for `ast` updates
- ✅ `functions`:
	- `set()` / `unset()` / `get()` / `stop()`
- ✅ `heredoc`:
	- correctly `unlink()` (best effort)
- ✅ `error`:
	- priorization helpers
- ✅ ``params`:
	- `process` module
- ✅ `walker`:
	- fully implemented
- ✅ `runner`:
	- fully implemented (error handling should be correct now)
- 🤔 **OLD**:
	- `void	print_unspecified_behaviour(const char *condition, const char *implementation)`
	- `EXP_DSQUOTE`:
		- process first, then apply all other expansions from the beginning of `word`
	- `utils`:
		- `scan_set_mode()` à déplacer dans un module `input_mode`
		- Utiliser `free_char_ptr_void()` au lieu de `free` comme callback pour les `vector_fre()` contenant des `char *`
	- replace `string_read_all()` by `posix_read()` and make `posix_read()` use `string_read_all()` (don't retry auto !)
	- Pour debug sous `Linux` => `launch.json` => `"MIMode": "gdb"`

# TODO

- `walker`:
	- `walk_case_expand()` : implement expansion incorrect len handling
- `error`:
	- `error_sys()`: requalify as `ERR_INTERNAL` if `errno == 0`
- `shell`:
	- process `ENV`:
		- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
		- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)
	- `shell_reset_unignored_traps()`: waiting for `trap` / `signal` implementation
- `builder`:
	- Split `builder/parser/qualifiers/build_table.c` into multiple files
- `libft`:
	- update `buff_get_index()` calls to handle new `ssize_t` return type + new form `buff_get_index_c()`
	- update `buff_append()`, `buff_prepend()`, `buff_insert()` et `buff_dup()` callers
	- ⚠️ Vérifier que les `buff_*()`, `vector_*()` etc de `libft` ne free pas en cas d'échec (sinon `errno` undefined):
		- 🚨 `buff_dup_n()` le fait !!
		- 🚨 `buff/format/append()` le fait !!
		- 🚨 `vector_dup()` le fait !!
		- 🚨 `vector_init()`, `vector_grow()` et `vector_dup()`, `vector_pop()`, `vector_insert()`, `vector_remove()` et `vector_merge()` retournent false dans d'autres cas qu'une erreur système !
	- Remove **wildcards** from `libft`'s `Makefile`
	- ⚠️ `libft/vector` => Arithmétique sur `void *` n'est pas **standard C**, c'est une **extension GCC** => Ok norme et compilation 42 ?!
	- ⚠️ `libft/vector` => Returns `false` on `libc` (`malloc`) failure **OR** `new_cap > SIZE_MAX / 2` !! (but `minishell` assumes `ERR_LIBC`!) => add `t_error` return type with `ERR_SIZE_MAX_REACHED` / `ERR_LIBC` value
- `ft_pidtostring()` et `ft_ltostring()` pour éviter double alloc
- `undefined_behaviour()`:
	- print la tête à Xavier
- `params`:
	- `variables`:
		- Switch `t_vector`s to `t_hashmap` ?
- `all`:
	- `clear()` API instead of `free()` for shell reset, subshell, etc (avoid rebuilding lr tables)
- **ALL REPO**:
	- use `print_unspecified_behaviour()`
	- Move `t_tokens` from `runner` to `token` module ?
	- Use `t_tokens` instead of `t_vector` of `t_token *` (`ast`...)
	- handle `options` properly (`-n` flag, ...)
	- `const` partout
	- `inline` partout
	- `assert` partout
	- `out_` prefix de tous les args qui sont **générés** par une fonction (cf `C#` syntax)
	- `ref_` prefix de tous les args qui sont **potentiellement modifiés** par une fonction (cf `C#` syntax)
	- use `posix_write()` instead of `write()`
	- use `posiw_open()` instead of `open()`
	- `errors`:
		- rename `ERR_LIBC` -> `ERR_SYS`
		- Ensure no `free()` / `libc` is done before `error_sys()`
		- Ensure all `error_print()` calls are **double** `NULL` terminated
		- handler `erros` at module-gates to only return meaning-full errors to callers
	- ⚠️ search for `open()` / `read()` / `write()` / ... remaining usages
	- `error_print()` return value must **NOT** be ignored (for `err.printed` update)
	- add doc + `make doc` / `github action`
	- **include** prototype header
	- ⚠️ don't call `undefined_behaviour()` when it's `unspecified`

---

# TO FIX

⚠️ All expansions can produce zero/one/multiple fields (check all `cmd_*_expansion_flags()` callers)
```bash
# TEST 1
set -- 'a' 'b' 'c'
for subject in 'abc' 'a b c' 'a' 'b' 'c'
do
    case $subject in
        $@) printf 'MATCH <%s>\n' "$subject" ;;
        *)  printf 'NO    <%s>\n' "$subject" ;;
    esac
done
# TEST 2
set -- 'a' 'b' 'c'
for subject in 'abc' 'a b c' 'a' 'b' 'c'
do
    case $subject in
        "$@") printf 'MATCH <%s>\n' "$subject" ;;
        *)  printf 'NO    <%s>\n' "$subject" ;;
    esac
done
```

---

# TESTS


## TESTS (MATCH PATTERN)

```bash
cat *	# should match all files in current dir
cat "*"	# should only match "*" file
```

## TESTS (IF)

```bash
# OK
echo "--------------------"
false
echo "before => $?"
if false || echo "in condition => $?"; then
	echo "inside => $?"
fi
echo "after => $?"
echo "--------------------"
```

```bash
# OK
echo "--------------------"
false
echo "before => $?"
if false; then
	echo NOP
fi
echo "after => $?"
echo "--------------------"
```

## TESTS (FOR)

```bash
# OK
echo "--------------------"
i=old
for i in a b c; do
    :
done
echo "should be 'c' => '$i'"
echo "--------------------"
```

```bash
# OK
echo "--------------------"
a=one
for x in $a $a; do
    a=two
    echo "shoud be 'one' => '$x'"
done
echo "--------------------"
```

```bash
# [RUNNER] error should have been requalified : 124 (variable assignment error)
echo "--------------------"
echo "should throw assignment error"
readonly i
for i in a b c; do
    echo "$i"
done
echo "--------------------"
```

## TESTS (SUBSHELL)

```bash
# ./minishell: builtin_break: not implemented
echo "--------------------"
while true; do
	(
		while true; do
			break 2
		done
		echo after
	)
	echo parent
done
echo "--------------------"
```

## TESTS (CASE)

```bash
# OK
echo "--------------------"
case x in
  x) ;;
esac
echo "\$? should be '0' => '$?'"
echo "--------------------"
```

# TEST (CASE : AFTER PATTERN MATCHING UPDATE)

```bash
echo "--------------------"
# OK (expected = abc*def)
v='abc*def'
echo "${v#'*'}"

# ERROR
p='*'
case abc in
    "$p") echo "ERROR: * should be litteral when p='*' and pattern is \"$p\"" ;;
	$p) echo "valid 1";;
esac

# OK
case '*' in
    \*) echo "valid 2" ;;
esac

# OK
case '?' in
    \?) echo "valid 3" ;;
esac

# OK
case '[' in
    \[) echo "valid 4" ;;
esac

# OK
case '[' in
    [) echo "valid 5" ;;
esac

# OK
case "" in
    "") echo "valid 6" ;;
esac
echo "--------------------"
```

## TESTS EXPANSIONS

```bash
# should assign ONLY if pattern is unset or NULL:
VAR=${pattern:=foo}
# Should NEVER assign during expansion:
VAR=${pattern}
VAR=${pattern:-foo}
VAR=${pattern+foo}
VAR=${pattern#foo}
VAR=${pattern%foo}
```

---

## MATHS AND ARITHMETIC EXPANSIONS

- [2.6.4 Arithmetic Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_04)
- [1.1.2.1 Arithmetic Precision and Operations](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_01_02_01)
- [1.1.2.2 Mathematical Functions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_01_02_02)

---

# BEFORE SUBMIT

- delete `assert()` calls
- delete `logs` lib
- delete `printf()` calls
- delete `*_dump.c` files and `*_dump()` functions
- delete `debug.h` and `debug.c`
- delete all `DEBUG` sections
- check all `TODO` comments

---

# UNSPECIFIED BEHAVIUOURS NOT IMPLEMENTED YET

## MAILPATH

- `The default message is unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `MAILPATH`)
- `The default messages for the various MAIL -related messages are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `RATIONALE`)

## vi Line Editing Insert Mode

- `If end-of-file is entered other than at the beginning of the line, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `EXTENDED DESCRIPTION` -> `vi Line Editing Insert Mode`)

---

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

- `runner/executor/resolver`:
	- No special treatment is done for `unspecified command names` so it can resolve to a `function` or an `external command`
- `functions`:
	- `assignments` persist after execution
- `utilities`:
	- unspecified utilities are processed as external utilities
- `errors`:
	- shell exists on `command not found` error when shell is not interactive
- ...

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
- Work as a **team** with `git` and `discord` (2 members):
	- **git branches**
	- **git issues**
	- **github actions** (`CI/CD`)
	- **discord hooks**
