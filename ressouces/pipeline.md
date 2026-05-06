- **per session** — runs once when the shell starts.
- **per input cycle** — once per "Enter" press in interactive mode; once per source-file read in non-interactive mode.
- **per token** — once for every token emitted.
- **per command** — once for every `simple_command` or `compound_command` actually selected for execution.
- **per word** — once for every `WORD`/`ASSIGNMENT_WORD`/`filename` in the command being executed.

| #  | Stage                                      | Input → Output                              | Frequency        | POSIX §           |
|----|--------------------------------------------|---------------------------------------------|------------------|-------------------|
| 1  | **Shell start-up** (process & env init)    | argv, envp → `t_shell` state                | per session      | §2.5.3, sh utility |
| 2  | **Startup-file execution** (`ENV`, `~/.profile` if login) | filename → executed commands | per session      | §2.5.3 (`ENV`), sh utility |
| 3  | **Prompt write** (PS1) — *interactive only* | `PS1` value → bytes on stderr               | per input cycle  | §2.5.3            |
| 4  | **Line read**                              | fd 0 (or file/`-c` string) → `char *`       | per input cycle  | §2.3 ("read its input in terms of lines"), sh |
| 5  | **Line-continuation folding** (`\<newline>` removal) | `char *` → `char *` (joined)        | per input cycle  | §2.2.1            |
| 6  | **Tokenization** (token recognition)       | folded `char *` → ordered `t_token[]` (raw, quotes preserved) | per input cycle | §2.3 |
| 7  | **Alias substitution** (re-lex)            | `t_token[]` → `t_token[]` (possibly more tokens) | per token (recursive) | §2.3.1   |
| 8  | **Token classification** (operator / IO_NUMBER / IO_LOCATION / TOKEN) | `t_token[]` → typed `t_token[]` | per token        | §2.10.1           |
| 9  | **Reserved-word promotion** (rule 1)       | typed token → reserved-word token where context permits | per token | §2.4, §2.10.1 rule 1 |
| 10 | **Parsing** (build AST)                    | typed `t_token[]` → `t_ast`                 | per input cycle  | §2.10.2           |
| 11 | **Heredoc body collection** (deferred phase-2 lex) | parser callback + raw input lines → heredoc payload attached to AST | per heredoc operator | §2.7.4, §2.3 ¶2 |
| 12 | **AST execution dispatch** (walk the tree, honor `&&`, `\|\|`, `;`, `&`) | `t_ast` → schedule of commands | per input cycle | §2.9.3 |
| 13 | **Per-command word-expansion pipeline**    | `WORD[]` → expanded `field[]`               | per command (× per word) | §2.6, §2.9.1.1 |
| 14 | **Redirection set-up**                     | redirection ops → fd table mutations (with save list for restoration) | per command | §2.7, §2.9.1.1 step 3 |
| 15 | **Variable-assignment application**        | `ASSIGNMENT_WORD[]` → env mutation (scope depends on builtin/function/external) | per command | §2.9.1.2 |
| 16 | **Command lookup**                         | command-name field → resolved special-builtin / function / regular-builtin / `PATH` hit | per command | §2.9.1.4 |
| 17 | **fork (if external)**                     | resolved command → child PID                | per external command | §2.9.1.6, fork() in XSH |
| 18 | **execve (in child)** *or* in-process call (builtin/function) | resolved command + argv + envp → running process | per external command | §2.9.1.6, execve() in XSH |
| 19 | **Wait & exit-status collection**          | child PID → `WEXITSTATUS` → `$?`            | per command (synchronous) | §2.8.2, §2.9.2 |
| 20 | **Redirection restoration**                | save list → fd table back to original       | per command      | §2.7 (implicit, see §2.13) |
| 21 | **Job-control bookkeeping** — *interactive (or non-interactive with `set -m`)* | child PID → jobs table | per command | §2.11 |
| 22 | **Trap delivery point**                    | pending signals → trap handler invocation   | between commands | §2.12, trap utility |
| 23 | **Loop**                                   | back to stage 3 (interactive) or stage 4 (non-interactive) | per input cycle | §2.1 |

### TTY-specific stages (only when `isatty(0)`)

- **3** PS1 write before each top-level command read (§2.5.3).
- **PS2 write** before *every* continuation line — see stage 4 sub-loop and §2.5.3, §2.7.4 ¶7.
- **GNU readline** integration (line editing, history) at stage 4. POSIX is silent on readline; the spec only requires that input be read in lines.
- **3-step job-control init** at start-up (§2.11): set foreground process group, install handlers for SIGINT/SIGQUIT/SIGTSTP/SIGTTIN/SIGTTOU.
- **Stage 21** is fully active only with `set -m` (default in interactive shells per §2.11).

### Non-TTY differences

- No PS1 / PS2 (POSIX makes those conditional on `isatty(stderr)` only by convention; §2.5.3 says PS2 is written before continuation lines but a non-TTY shell has no place to display it usefully — emit anyway only if the spec is read literally; **most shells gate this on `isatty`**).
- Input source is a script file, here-string passed by `-c`, or `system()`/`popen()` (§2.1 ¶3).
- A shell error in stage 6/8/10 *exits* the shell (§2.8.1 table), whereas an interactive shell continues at stage 3.
- No job control unless `set -m` is given (§2.11).
- Reading is stream-oriented: `read(0, …)` or `fread()`; line continuation folding still applies (§2.2.1).

### Shell-error consequences (§2.8.1, governs stages 6–18)

| Error type | Interactive | Non-interactive |
|---|---|---|
| Shell language syntax error | Print, do not exit shell | Exit shell |
| Redirection error on special builtin | Print, do not exit | Exit shell |
| Redirection error on other utility | Print, command fails | Print, command fails |
| Variable assignment error on special builtin | Print, do not exit | Exit shell |
| Expansion error (e.g. `${x:?}`) | Print, do not exit | Exit shell |
| Command not found | `$?` ← 127 | `$?` ← 127 |

This table dictates how stages 10/13/14/15 must signal failure back to the dispatcher in stage 12.
