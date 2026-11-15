*This project has been created as part of the 42 curriculum by gastesan, adouieb.*

# minishell

## Description

A POSIX-oriented command interpreter written in C as part of the 42 curriculum.

`minishell` aims to follow the [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html) and the [`sh` utility](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) specification (POSIX.1-2024, Issue 8) as closely as the 42 allowed-functions list permits. It does not yet claim full POSIX compliance: arithmetic expansion, job control and the remaining options and built-ins are planned for the `42sh` project, once all C functions are allowed.

When POSIX leaves a behaviour *unspecified*, the shell prints a warning that cites the relevant POSIX section and describes the behaviour it chose instead.

## Overview

### Repository layout

```text
minishell/
├── 1_grammar/                 POSIX grammar rules, symbols and token qualifiers
├── 2_generator/               LR(1) parser-table generator (builds lr_generator)
├── 3_lr_tables/               LR parser tables
│   ├── 1_base/                checked-in fallback tables
│   └── 2_generated/           tables generated at build time
├── 4_shell/                   the shell itself
│   ├── includes/              public headers
│   └── srcs/
│       ├── 1_shell/           shell life cycle, subshells
│       ├── 2_scanner/         reader, lexer, here-documents
│       ├── 3_builder/         LR parser (CST) and CST → AST converter
│       ├── 4_runner/          AST walker, pipelines, xtrace
│       ├── builtins/          built-in utilities
│       ├── cmd/               command resolution, PATH search, dispatch
│       ├── cmd_sub/           command substitution
│       ├── env/               options, parameters, variables, functions,
│       │                      processes, signals, aliases, fds
│       ├── expander/          word expansions
│       ├── history/           interactive history
│       ├── redirector/        redirections
│       └── main.c
├── docs/                      internal documentation and work notes
├── libft/                     utility library and data structures (git submodule)
├── tests/                     POSIX behaviour test suite (zsh)
│   ├── suites/                test cases, grouped by theme, and the harness
│   ├── test_posix_suite.zsh   main test runner
│   ├── download_and_run_posix_suite.zsh
│   │                          standalone launcher: downloads and runs the suite
│   ├── test_exec.c            helper that prints its argv (built by the runner)
│   └── readline.supp          valgrind suppressions for readline leaks
└── Makefile
```

### How the shell works

The parser tables are generated **at build time**. The generator reads the POSIX grammar in `1_grammar/` and writes C tables into `3_lr_tables/2_generated/`, which are compiled into the shell. At runtime, every command goes through three stages:

```text
input ──▶ scanner ──▶ builder ──▶ runner
          (lexer)     (parser)    (executor)
```

| Stage | Location | Role |
| --- | --- | --- |
| **Scanner** | `4_shell/srcs/2_scanner` | Reads input (readline, script file, `-c` string or piped stdin) and splits it into POSIX tokens: operators, words, newlines, comments and here-document bodies. It tracks nested quoting and substitution contexts (`'…'`, `"…"`, `$'…'`, `$(…)`, `` `…` ``, `${…}`, `$((…))`) and expands aliases. |
| **Builder** | `4_shell/srcs/3_builder` | An **LR(1) parser** driven by the generated tables. It builds a concrete syntax tree (CST) and converts it into an abstract syntax tree (AST). |
| **Runner** | `4_shell/srcs/4_runner` | Walks the AST: expands words, applies redirections, assigns variables, resolves commands and runs them. |

Supporting modules in `4_shell/srcs`:
- `expander`: word expansions.
- `cmd`: command resolution, `PATH` search and dispatch.
- `redirector`: redirections.
- `env`: options, special and positional parameters, variables, functions, child processes, command hash cache, file descriptors, signals and aliases.
- `history`: interactive history.
- `builtins`: the built-in utilities.
- `cmd_sub`: command substitution.

## Instructions

### Requirements

- A C compiler available as `cc`, and `make`
- GNU **Readline** (development headers and library)
  - Debian / Ubuntu: `sudo apt install build-essential libreadline-dev`
  - macOS: `brew install readline` (the Makefile finds it with `brew --prefix readline`)
- `zsh`, only to run the test suite

### Getting the libft submodule

`minishell` depends on a custom C library, **libft**, included as a git submodule in `libft/` (source: <https://github.com/guillaumeast/42_libft>). Fetch it before building, or `libft/` will be empty and compilation will fail.

Clone with submodules:

```sh
git clone --recurse-submodules git@github.com:Eraz19/minishell.git
cd minishell
```

If you already cloned without `--recurse-submodules`:

```sh
git submodule update --init --recursive
```

After a `git pull`, update libft to the commit recorded by the repository:

```sh
git submodule update --recursive
```

You do not need to build libft yourself: the main Makefile runs `make -C libft` and links `libft/libft.a`.

### Compilation

From the repository root, run:

```sh
make
```

The build compiles libft, then builds the grammar and the table generator and generates the LR tables. It skips table generation when nothing in the grammar or generator has changed. Finally it compiles and links `minishell`.

| Command | Effect |
| --- | --- |
| `make` / `make all` | Builds `minishell` (`-Wall -Wextra -Werror -O2`). |
| `make bonus` | Same as `make`. |
| `make tables` | Only (re)generates the LR parser tables. |
| `make debug` | Full rebuild with `-O0 -g3` plus AddressSanitizer and UBSan. |
| `make test` | Full rebuild, then runs the POSIX test suite (`tests/test_posix_suite.zsh`). |
| `make clean` | Removes object files, the table generator, and test fixtures and logs. |
| `make fclean` | `clean`, plus removes `minishell` and `libft.a` and resets the generated tables to the checked-in base copy. |
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
| `./minishell` | Reads commands from standard input. If stdin and stderr are terminals, the shell is **interactive**: it shows a prompt, offers line editing and history (readline), and enables `-m`. |
| `./minishell script.sh a b` | Runs commands from `script.sh`, with `$0` = `script.sh`, `$1` = `a`, `$2` = `b`. |
| `./minishell -c 'echo $1' name x` | Runs the command string, with `$0` = `name`, `$1` = `x`. |
| `./minishell -s a b` | Reads commands from stdin, with the positional parameters set to `a b`. |
| `echo 'ls' \| ./minishell` | Non-interactive stdin (pipe) mode. |

`-` turns an option on and `+` turns it off. You can combine single-letter flags (`-ex`), and `--` ends option parsing. Leave an interactive session with `exit` or `Ctrl-D`.

### Options

Invocation options. You can also change them at runtime with `set`, except `-c`, `-i` and `-s`:

| Flag | `-o` name | Description | Status |
| --- | --- | --- | --- |
| `-a` | `allexport` | Export every variable that is assigned. | ✅ |
| `-C` | `noclobber` | `>` refuses to overwrite an existing regular file; use `>\|` to force it. | ✅ |
| `-e` | `errexit` | Exit when an AND-OR list fails (commands in a negated `!` pipeline are exempt). | ✅ (partial) |
| `-f` | `noglob` | Turn off pathname expansion (globbing). | ✅ |
| `-h` | — | Remember (hash) command locations as they are looked up. | ✅ |
| `-m` | `monitor` | Monitor mode; on by default in an interactive shell. | ✅ (partial, see [Limitations](#limitations)) |
| `-n` | `noexec` | Read and parse commands without running them (syntax check). | ✅ |
| `-u` | `nounset` | Treat expansion of an unset parameter as an error. | ✅ |
| `-x` | `xtrace` | Print each expanded command to stderr, prefixed by `$PS4`, before running it. | ✅ |
| `-c` | — | Read commands from the `command_string` operand. | ✅ |
| `-i` | — | Force interactive mode. | ✅ |
| `-s` | — | Read commands from standard input. | ✅ |
| — | `ignoreeof` | An interactive shell does not exit on `Ctrl-D`. | ✅ |
| — | `pipefail` | A pipeline's exit status is that of the last command that failed, not of the last command. | ✅ |
| `-b` | `notify` | Report background job status asynchronously. | accepted, no effect yet |
| `-v` | `verbose` | Echo input lines as they are read. | accepted, no effect yet |
| — | `vi` | vi-style line editing. | accepted, no effect yet |
| — | `nolog` | Do not store function definitions in history. | accepted, no effect yet |

`echo $-` shows the active single-letter options.

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
- **Functions**: `name() compound-command [redirections]`, called with their own positional parameters; leave a function with `return`
- **Loop control**: `break [n]` and `continue [n]`
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

Here-documents are expanded (parameters, command substitution) unless any part of the delimiter is quoted.

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
5. **Pathname expansion** (globbing): `*`, `?`, `[…]`, `[!…]`
6. **Quote removal**

### Variables and environment

- The environment is imported at startup. Required variables are initialised as needed: `PWD`, `IFS`, `PPID`, `PS1` (`$ `), `PS2` (`> `), `PS4` (`+ `).
- Variables can be exported (`export`) and marked read-only (`readonly`).
- Assignments placed before a command apply to that command's environment only.

### Interactive shell

- Line editing and prompts through GNU **readline**, using `$PS1` and `$PS2` (continuation prompt)
- **Persistent history**, stored in `$HISTFILE` (default `$HOME/.sh_history`), with its size limited by `$HISTSIZE`
- **Signals**: `Ctrl-C` interrupts the current line or foreground command, `Ctrl-\` is ignored by the shell, and `Ctrl-D` exits (unless `ignoreeof` is set)
- `SIGTERM`, `SIGTTIN`, `SIGTTOU` and `SIGTSTP` are ignored by the interactive shell

### Command resolution

Commands are resolved in POSIX order:

1. special built-ins
2. functions
3. intrinsic built-ins
4. `PATH` search, using the command hash table

When the `PATH` search resolves to the system `echo`, `env` or `pwd` (in `/bin` or `/usr/bin`), the shell runs its own built-in version of that utility instead of the external program.

## Built-ins

| Built-in | Type | Supported syntax |
| --- | --- | --- |
| `:` | special | `: [args]`: does nothing, returns 0 |
| `.` | special | `. file`: runs `file` in the current environment (searched in `PATH` if it has no `/`) |
| `break` | special | `break [n]` |
| `continue` | special | `continue [n]` |
| `eval` | special | `eval [args]…` |
| `exit` | special | `exit [n]` |
| `export` | special | `export [-p] [name[=value]]…` |
| `readonly` | special | `readonly [-p] [name[=value]]…` |
| `return` | special | `return [n]` |
| `set` | special | `set [-abCefhmnuvx] [-o opt] [+o opt] [--] [args]…`; `set` alone lists variables, and `set -o` / `set +o` list options |
| `shift` | special | `shift [n]` |
| `trap` | special | `trap [-p] [action condition…]`; supports signal names and numbers, and `EXIT` |
| `unset` | special | `unset [-f\|-v] name…` |
| `alias` | intrinsic | `alias [name[=value]]…` |
| `cd` | intrinsic | `cd [-L\|-P [-e]] [dir\|-]`; uses `CDPATH`, `OLDPWD`, `PWD` |
| `unalias` | intrinsic | `unalias [-a] name…` |
| `wait` | intrinsic | `wait [pid…]` |
| `echo` | regular | `echo [-neE] [string…]`; `-e` enables backslash escapes |
| `env` | regular | `env [-i] [name=value]… [utility [args]]` |
| `pwd` | regular | `pwd [-L\|-P]` |

Other POSIX built-ins such as `exec`, `times`, `read`, `kill`, `jobs`, `fg`, `bg`, `umask` and `type` are not built into the shell. If an external program with that name exists in `PATH`, it runs instead.

For names whose behaviour POSIX leaves unspecified (`source`, `local`, `declare`, `history`, `pushd`, …), the shell prints an *unspecified behaviour* warning and continues normal lookup (function, then `PATH`).

## Limitations

The 42 subject allows only a small set of libc functions, so some parts of POSIX are emulated or left out. The full list, including how unspecified POSIX behaviours are handled, is in [docs/1_reference/POSIX_COMPLIANCE.md](docs/1_reference/POSIX_COMPLIANCE.md); the rest of the internal documentation and work notes are in [docs/](docs/).

- **Arithmetic expansion** `$((…))` is parsed but not evaluated.
- **Job control** (`fg`, `bg`, `jobs`, process groups) is not available because `setpgid()`, `tcsetpgrp()` and `setsid()` are forbidden.
- Process and user IDs (`getpid`, `getppid`, `getuid`, `geteuid`, `getgid`, `getegid`) come from small replacements in `4_shell/srcs/0_asm_stubs/`. They use assembly syscall stubs on macOS, and `/proc` on Linux. OpenBSD blocks syscalls made from outside libc, so the shell is not fully compliant there.
- **Pattern matching** ignores locales: bracket ranges and character classes use byte/ASCII semantics.
- **Signal names** for `trap` come from a compile-time table, so implementation-defined signals the table does not include are rejected.
- Without `fcntl()`, `>&` / `<&` check only that the target fd is open, not its access mode. Backup fds are closed by hand before `execve()` because they cannot be marked close-on-exec.

## Testing

Build `minishell`, then run the POSIX behaviour suite from the project root:

```sh
make test                                   # rebuild, then run every suite
tests/test_posix_suite.zsh                  # run against ./minishell
tests/test_posix_suite.zsh --suite builtins # a single suite
tests/test_posix_suite.zsh --filter CD-     # only cases whose ID starts with CD-
tests/test_posix_suite.zsh --leak           # run every case under valgrind
```

Suites: `options`, `builtins`, `ast`, `complex`, `words`, `semantics`, `custom` (see `--list`). Other options: `--timeout N`, and `--td` to also run the cases for features that are not implemented yet. Detailed case reports are written to `tests/logs/`.

To run the suite on a machine without the repository, download and run it as a standalone script:

```sh
curl -fsSL https://raw.githubusercontent.com/Eraz19/minishell/master/tests/download_and_run_posix_suite.zsh | zsh
curl -fsSL https://raw.githubusercontent.com/Eraz19/minishell/master/tests/download_and_run_posix_suite.zsh \
  | zsh -s -- ./minishell --suite builtins --filter CD-
```

The script downloads the test runner, compiles its small C helper and runs the suite against `./minishell`. Downloaded files and reports are kept in `.minishell-posix-suite/`. It requires Zsh, `cc`, `timeout`, and either `curl` or `wget`; Valgrind is only needed for `--leak`. On macOS, install GNU coreutils so that `timeout` is in `PATH`.

## Resources

References used to understand and validate shell behaviour:

- [POSIX.1-2024 - sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html)
- [POSIX.1-2024 - Chapter 1: Introduction (utilities, built-ins…)](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html)
- [POSIX.1-2024 - Chapter 2: Shell Command Language](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html)
- [XBD 12. - Utility Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap12.html)
- Alfred V. Aho, Monica S. Lam, Ravi Sethi, and Jeffrey D. Ullman, *Compilers: Principles, Techniques, and Tools*: background for the LR parser and parser-table generation.
- [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
- [Design chart](https://excalidraw.com/#room=01ba22c634c41561fdf2,vhhfkBWmOlkE0CxGHVoCBw)

### Use of AI

- [Bash Deep Wiki](https://deepwiki.com/tianon/mirror-bash)
- [Custom expert POSIX GPT](https://chatgpt.com/g/g-69fa0daffc00819183d8189e92ad1c1d-posix-gpt)

AI tools were used as an assistance layer for repetitive documentation work, the design and expansion of automated POSIX test cases, investigation of edge cases, and review suggestions during debugging and refactoring. They also helped draft this README and the bootstrap script used to download the external test suite. Behavioral decisions were checked against the POSIX references above, and suggested changes were reviewed, compiled, and tested before being retained.

## Authors

- gastesan ([guillaumeast](https://github.com/guillaumeast))
- adouieb ([Eraz19](https://github.com/Eraz19))
