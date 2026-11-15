*This project has been created as part of the 42 curriculum by gastesan, adouieb.*

# Minishell

## Description

Minishell is a POSIX shell written in C. Its primary goal is to reproduce the core behavior of a command-line shell while exploring process creation, file descriptors, signals, parsing, expansion, and command execution.

The project implements the mandatory 42 Minishell requirements and extends them with a larger subset of the POSIX Shell Command Language. It targets POSIX.1-2024 (Issue 8) where the 42 function whitelist permits it, but it does not claim complete POSIX compliance (yet).

Therefore, *arithmetic expansion*, full *match pattern*, *job control* and missing *options* and *builtins* will be implemented for `42_sh` project, once all C functions will be allowed.

Major capabilities include:

- interactive input with *Readline*, *command history*, and *signal handling*;
- executable lookup through `PATH`, relative paths, and absolute paths;
- *pipelines*, *asynchronous lists*, and input/output *redirections*, including *here-documents*;
- *single and double quotes*, *parameter expansion*, *command substitution*, *field splitting*, *pathname expansion*, *tilde expansion*, and *quote removal*;
- `&&`, `||`, *subshells*, *brace groups*, `if`, `while`, `until`, `for`, `case`,
  and *shell functions*;
- *built-ins* including `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`,
  `alias`, `unalias`, `readonly`, `set`, `shift`, `trap`, `wait`, `eval`,
  `return`, `break`, `continue`, `.`, and `:`;
- shell invocation modes and *options* such as `-c`, `-s`, `-a`, `-C`, `-e`,
  `-f`, `-h`, `-i`, `-n`, `-x`, `pipefail`, and `ignoreeof`.

### Architecture

```text
1_grammar/      POSIX grammar rules and token qualifiers
2_generator/    LR parser-table generator
3_lr_tables/    generated parser tables and checked-in fallback tables
4_shell/        scanner, parser, CST-to-AST converter, expander, and runner
libft/          project utility library and data structures
```

Input is tokenized by the `scanner` and consumed by the `LR parser`. The resulting *concrete syntax tree (CST)* is converted to an *AST*, *expanded*, and finally *executed* by the `runner`. *Environment* state, *file descriptors*, *processes*, *signals*, *aliases*, *functions*, and shell *options* are managed by dedicated subsystems.

## Instructions

### Requirements

The project requires:

- a C compiler available as `cc`;
- `make`;
- the `Readline` development headers and library.

On Debian or Ubuntu, the required packages can be installed with:

```sh
sudo apt install build-essential libreadline-dev
```

On macOS with Homebrew:

```sh
brew install readline
```

### Compilation

From the repository root, run:

```sh
make
```

This generates the LR parsing tables when necessary and builds the `minishell` executable. The available maintenance targets are:

```sh
make clean    # remove object files and generated test output
make fclean   # also remove minishell and generated build artifacts
make re       # perform a complete rebuild
```

The `bonus` target builds the same executable with the additional shell features included:

```sh
make bonus
```

### Execution

Start an interactive shell with:

```sh
./minishell
```

It can also execute a command string or a script file:

```sh
./minishell -c 'printf "hello from minishell\n"'
./minishell path/to/script.sh argument1 argument2
```

Use `exit` or send an end-of-file with `Ctrl-D` to leave an interactive session.

## Testing

Build `minishell` first, then run the current POSIX behavior suite directly from the project root:

```sh
curl -fsSL https://raw.githubusercontent.com/Eraz19/minishell/submission/run_posix_suite.zsh | zsh
```

The launcher downloads the current test runner and all of its dependencies, compiles its small C helper for the evaluator's machine, and runs the suite against `./minishell`. Downloaded files and reports are kept under
`.minishell-posix-suite/`; detailed case reports are written to
`.minishell-posix-suite/tests/logs/`.

The suite requires Zsh, `cc`, `timeout`, and either `curl` or `wget`. Valgrind is only required when using `--leak`. On macOS, install GNU coreutils and make sure `timeout` is available in `PATH`.

An executable path and test options can be passed after `zsh -s --`. For example:

```sh
curl -fsSL https://raw.githubusercontent.com/Eraz19/minishell/submission/run_posix_suite.zsh \
  | zsh -s -- ./minishell --suite builtins --filter CD-
```

Useful options include `--suite`, `--filter`, `--timeout`, `--leak`, `--td`, and `--list`.

## Resources

The following references were used to understand and validate shell behavior:

- [POSIX.1-2024 - sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html)
- [POSIX.1-2024 - Chapitre 1: Precision, utilities, builtins....](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html)
- [POSIX.1-2024 - Chapitre 2: Shell Command Language](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html)
- [XBD 12. - Utility Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap12.html)
- Alfred V. Aho, Monica S. Lam, Ravi Sethi, and Jeffrey D. Ullman,
  *Compilers: Principles, Techniques, and Tools* — background for the LR parser
  and parser-table generation.
- [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
- [Design chart](https://excalidraw.com/#room=01ba22c634c41561fdf2,vhhfkBWmOlkE0CxGHVoCBw)

### Use of AI

- [Bash Deep Wiki](https://deepwiki.com/tianon/mirror-bash)
- [Custom expert POSIX GPT](https://chatgpt.com/g/g-69fa0daffc00819183d8189e92ad1c1d-posix-gpt)

AI tools were used as an assistance layer for repetitive documentation work, the design and expansion of automated POSIX test cases, investigation of edge cases, and review suggestions during debugging and refactoring. They also helped draft this README and the bootstrap script used to download the external test suite. Behavioral decisions were checked against the POSIX references above, and suggested changes were reviewed, compiled, and tested before being retained.
