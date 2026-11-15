# minishell

A POSIX-oriented command interpreter written in C as part of the 42 curriculum.

`minishell` aims to follow the [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html) and the [`sh` utility](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) specification as closely as the 42 allowed-functions list permits. When POSIX leaves a behaviour *unspecified*, the shell prints a warning that cites the relevant POSIX section and describes the behaviour it chose instead.

## Overview

The shell is built as three main modules connected in a pipeline:

```
input ──▶ scanner ──▶ builder ──▶ runner
          (lexer)     (parser)    (executor)
```

| Module | Location | Role |
| --- | --- | --- |
| **Scanner** | `srcs/2_scanner`, `srcs/lexer` | Reads input (readline, file, string or pipe) and splits it into POSIX tokens: operators, words, newlines, comments, here-document bodies. It tracks nested quoting and substitution contexts (`'…'`, `"…"`, `$'…'`, `$(…)`, `` `…` ``, `${…}`, `$((…))`) and expands aliases. |
| **Builder** | `srcs/3_builder` | An **LR(1) parser** generated at startup from the POSIX grammar (`ressouces/grammar.txt`). It builds a concrete syntax tree (CST) and converts it into an abstract syntax tree (AST). |
| **Runner** | `srcs/4_runner` | Walks the AST: expands words, applies redirections, assigns variables, resolves commands (special built-in, function, built-in or external `PATH` lookup with a hash cache) and runs them. |

Supporting modules: `expander` (word expansions), `params` (options, special and positional parameters, variables, functions, child processes), `history`, `alias`, `signal` and `cmd_sub`.

## Building

### Requirements

- A C compiler (`cc`) and `make`
- GNU **readline** (development headers and library)
  - Linux (Debian/Ubuntu): `sudo apt install libreadline-dev`
  - macOS: `brew install readline` (the Makefile finds it with `brew --prefix readline`)
- `zsh`, only to run the test scripts (`make test`)

### Getting the libft submodule

`minishell` depends on a custom C library, **libft**, included as a git submodule in `libft/` (source: <https://github.com/guillaumeast/42_libft>). The submodule must be fetched before building, or the `libft/` directory will be empty and compilation will fail.

Clone with submodules:

```sh
git clone --recurse-submodules git@github.com:Eraz19/minishell.git
cd minishell
```

If you already cloned without `--recurse-submodules`:

```sh
git submodule update --init --recursive
```

To update libft to the commit recorded by the repository after a `git pull`:

```sh
git submodule update --recursive
```

You do not need to build libft on its own: the main Makefile runs `make -C libft` to build `libft/libft.a` and links it.

### Make targets

| Command | Effect |
| --- | --- |
| `make` / `make all` | Builds libft, then the `minishell` binary (`-Wall -Wextra -Werror -O2`). |
| `make bonus` | Same as `make`. |
| `make debug` | Full rebuild with `-O0 -g3`, AddressSanitizer + UBSan, and all `DEBUG_*` trace flags enabled (logs, parameters, parsing, CST/AST dumps, history, command substitution). |
| `make test` | Builds, then runs every `tests/*.zsh` test script. |
| `make clean` | Removes object files (`obj/`), test fixtures/logs and libft objects. |
| `make fclean` | `clean` + removes the `minishell` binary and `libft.a`. |
| `make re` | `fclean` + `all`. |

## Usage

`minishell` follows the `sh` invocation syntax:

```sh
./minishell [-abCefhimnuvx] [-o option]... [+abCefhimnuvx] [+o option]...
./minishell [options] script_file [argument...]
./minishell [options] -c command_string [command_name [argument...]]
./minishell [options] -s [argument...]
```

| Form | Input mode |
| --- | --- |
| `./minishell` | Reads commands from standard input. If stdin and stderr are terminals, the shell is **interactive**: it shows a prompt, keeps history and line editing (readline), and enables `-m`. |
| `./minishell script.sh a b` | Runs commands from `script.sh`. `$0` is `script.sh`, and `$1`, `$2`… are `a`, `b`. |
| `./minishell -c 'echo $1' name x` | Runs the command string. `$0` is `name`, `$1` is `x`. |
| `./minishell -s a b` | Reads commands from stdin while setting the positional parameters to `a b`. |
| `echo 'ls' \| ./minishell` | Non-interactive stdin (pipe) mode. |

`-` turns an option on and `+` turns it off. You can combine single-letter flags (`-ex`), and `--` ends option parsing.

### Options

Invocation options, which can also be changed at runtime with `set` (except `-c`, `-i` and `-s`):

| Flag | `-o` name | Description | Status |
| --- | --- | --- | --- |
| `-a` | `allexport` | Export every variable that is assigned. | ✅ |
| `-C` | `noclobber` | `>` refuses to overwrite an existing regular file; use `>\|` to force it. | ✅ |
| `-f` | `noglob` | Turn off pathname expansion (globbing). | ✅ |
| `-h` | — | Remember (hash) command locations as they are looked up. | ✅ |
| `-m` | `monitor` | Monitor mode; on by default in an interactive shell. | ✅ (partial, see [Limitations](#limitations)) |
| `-n` | `noexec` | Read and parse commands without running them (syntax check). | ✅ |
| `-x` | `xtrace` | Print each expanded command to stderr, prefixed by `$PS4`, before running it. | ✅ |
| `-c` | — | Read commands from the `command_string` operand. | ✅ |
| `-i` | — | Force interactive mode. | ✅ |
| `-s` | — | Read commands from standard input. | ✅ |
| — | `ignoreeof` | Interactive shell does not exit on `Ctrl-D`. | ✅ |
| — | `pipefail` | A pipeline's exit status is that of the last command that failed, not of the last command. | ✅ |
| `-b` | `notify` | Report background job status asynchronously. | accepted, no effect yet |
| `-e` | `errexit` | Exit when a command fails. | accepted, no effect yet |
| `-u` | `nounset` | Treat expansion of an unset variable as an error. | accepted, no effect yet |
| `-v` | `verbose` | Echo input lines as they are read. | accepted, no effect yet |
| — | `vi` | vi-style line editing. | accepted, no effect yet |
| — | `nolog` | Do not store function definitions in history. | accepted, no effect yet |

The active single-letter options can be read with `echo $-`.

## Features

### Command syntax

- **Simple commands** with variable assignments, words and redirections: `VAR=value cmd arg > out`
- **Pipelines**: `cmd1 | cmd2 | cmd3`, including negation with `! cmd`
- **AND / OR lists**: `cmd1 && cmd2 || cmd3`
- **Sequential lists**: `cmd1 ; cmd2`, and newlines
- **Asynchronous lists**: `cmd &` (runs in a forked subshell; `$!` and `wait` are supported)
- **Grouping**: subshells `( list )` and brace groups `{ list ; }`
- **Compound commands**:
  - `if … then … elif … else … fi`
  - `while … do … done` and `until … do … done`
  - `for name [in words…] do … done`
  - `case word in pattern|pattern) … ;; esac`, with `;;` and `;&` (fall-through)
- **Functions**: `name() compound-command [redirections]`, called with their own positional parameters
- **Comments**: `# …`
- **Aliases**: alias substitution on command words (`alias` / `unalias`)
- **Reserved words** are recognised in the correct grammar positions (`if`, `then`, `else`, `elif`, `fi`, `do`, `done`, `case`, `esac`, `while`, `until`, `for`, `in`, `{`, `}`, `!`)

### Redirections

All POSIX redirection operators, each with an optional file descriptor prefix `[n]`:

| Operator | Meaning |
| --- | --- |
| `[n]< file` | Input |
| `[n]> file` | Output (truncate; respects `noclobber`) |
| `[n]>\| file` | Output, ignoring `noclobber` |
| `[n]>> file` | Append |
| `[n]<> file` | Open for reading and writing |
| `[n]<& word` / `[n]>& word` | Duplicate an fd, or close it with `-` |
| `[n]<< delim` | Here-document |
| `[n]<<- delim` | Here-document with leading tabs stripped |

Here-documents are expanded (parameters, command substitution) unless any part of the delimiter is quoted. User fds 0–128 are supported.

### Quoting

- Backslash escapes: `\c`
- Single quotes: `'literal'`
- Double quotes: `"allows $expansions"`
- Dollar-single quotes: `$'\n\t\x41\101…'` (ANSI-C style escape sequences)

### Expansions

Expansions run in POSIX order:

1. **Tilde expansion**: `~`, `~user`, and in assignments
2. **Parameter expansion**:
   - `$name`, `${name}`, positional parameters `$1`… `${10}`
   - Special parameters: `$?`, `$$`, `$!`, `$#`, `$@`, `$*`, `$-`, `$0`
   - Length: `${#name}`
   - Default / assign / error / alternative values: `${p:-w}`, `${p-w}`, `${p:=w}`, `${p=w}`, `${p:?w}`, `${p?w}`, `${p:+w}`, `${p+w}`
   - Pattern removal: `${p#pat}`, `${p##pat}`, `${p%pat}`, `${p%%pat}`
3. **Command substitution**: `$(command)` and `` `command` ``, including nesting
4. **Field splitting** using `$IFS`
5. **Pathname expansion** (globbing): `*`, `?`, `[…]`, `[!…]`, with bracket ranges and character classes
6. **Quote removal**

### Variables and environment

- The environment is imported at startup. Required variables are initialised as needed: `PWD`, `IFS`, `PPID`, `PS1` (`$ `), `PS2` (`> `), `PS4` (`+ `).
- Variables can be exported (`export`) and marked read-only (`readonly`).
- Assignments placed before a command apply to that command's environment only.

### Interactive shell

- Line editing and prompt through GNU **readline**, with `$PS1` and `$PS2` (continuation prompt)
- **Persistent history**, stored in `$HISTFILE` (default `$HOME/.sh_history`), with its size limited by `$HISTSIZE`
- **Signals**: `Ctrl-C` interrupts the current line or foreground command, `Ctrl-\` is ignored by the shell, and `Ctrl-D` exits (unless `ignoreeof` is set)
- `SIGTTIN`, `SIGTTOU` and `SIGTSTP` are ignored

### Command resolution

Commands are resolved in POSIX order:

1. special built-ins
2. functions
3. intrinsic built-ins
4. `PATH` search, using the command hash table

When the `PATH` search resolves to `/bin/echo`, `/usr/bin/env` or `/bin/pwd`, the shell runs its own built-in version of that utility instead of the external program.

## Built-ins

### Implemented

| Built-in | Type | Supported syntax |
| --- | --- | --- |
| `:` | special | `: [args]`: does nothing, returns 0 |
| `exit` | special | `exit [n]` |
| `export` | special | `export [-p] [name[=value]]…` |
| `readonly` | special | `readonly [-p] [name[=value]]…` |
| `set` | special | `set [-abCefhmnuvx] [-o opt] [+o opt] [--] [args]…`; `set` alone lists variables, `set -o` / `set +o` list options |
| `unset` | special | `unset [-f\|-v] name…` |
| `trap` | special | `trap [-p] [action condition…]`; supports signal names/numbers and `EXIT` |
| `cd` | intrinsic | `cd [-L\|-P [-e]] [dir\|-]`; uses `CDPATH`, `OLDPWD`, `PWD` |
| `alias` | intrinsic | `alias [name[=value]]…` |
| `unalias` | intrinsic | `unalias [-a] name…` |
| `wait` | intrinsic | `wait [pid…]` |
| `echo` | regular | `echo [-neE] [string…]`; `-e` enables backslash escapes |
| `pwd` | regular | `pwd [-L\|-P]` |
| `env` | regular | `env [-i] [name=value]… [utility [args]]` |

### Recognised but not yet implemented

These names resolve as built-ins but currently print a *not implemented* error:

- special: `break`, `continue`, `.`, `eval`, `exec`, `return`, `shift`, `times`
- intrinsic: `bg`, `fg`, `jobs`, `command`, `fc`, `getopts`, `hash`, `kill`, `read`, `type`, `ulimit`, `umask`

For names whose behaviour POSIX leaves unspecified (`source`, `local`, `declare`, `history`, `pushd`, …), the shell prints an *unspecified behaviour* warning and continues normal lookup (function, then `PATH`).

## Limitations

The 42 subject allows only a small set of libc functions, so some parts of POSIX are emulated or left out:

- **Arithmetic expansion** `$((…))` is parsed but not evaluated yet.
- **Job control** (`fg`, `bg`, `jobs`, process groups) is not available because `setpgid()`, `tcsetpgrp()` and `setsid()` are forbidden.
- `getpid()` and `getppid()` are replaced by small assembly stubs (macOS ARM/x86) or by reading `/proc` (Linux/FreeBSD) to initialise `$$` and `$PPID`. On OpenBSD the syscall stubs are blocked, so full compliance is not possible there.
- **Pattern matching** ignores locales: bracket ranges and character classes use byte/ASCII semantics.
- **Signal names** for `trap` come from a compile-time table, so implementation-defined signals the table does not include are rejected.
- Without `fcntl()`, `>&` / `<&` check only that the target fd is open, not its access mode. Backup fds are closed by hand before `execve()` because they cannot be marked close-on-exec.

## Authors

- Alexander ([Eraz19](https://github.com/Eraz19))
- Guillaume ([guillaumeast](https://github.com/guillaumeast))
