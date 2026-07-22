#ifndef BUILTINS_H
# define BUILTINS_H

# include "error.h"
# include "runner_type.h"
# include <stdbool.h>

/** @defgroup builtins Built-in utilities
 *  @brief POSIX.1-2024 built-ins, executed in the shell process.
 *
 *  Every built-in follows the same contract (@ref t_builtin): it writes
 *  the utility's POSIX exit status into @c exit_status (0 on success,
 *  the raw error type value otherwise), prints its own diagnostics
 *  prefixed with the utility name (the most specific point), and
 *  requalifies its return before crossing the API: user-facing
 *  failures become @c ERR_BUILTIN (the executor maps it to
 *  @c ERR_POSIX_BUILTIN_SPECIAL for special built-ins, per POSIX 2.8.1
 *  a non-interactive shell then exits), broken shell state becomes
 *  @c ERR_INTERNAL, @c ERR_LIBC and @c ERR_INTERRUPTED pass through.
 *
 *  Unspecified or undefined POSIX behaviours are surfaced at runtime
 *  with @c print_unspecified_behaviour / @c undefined_behaviour, with
 *  the citation and the documented choice.
 */

/**
 * @ingroup builtins
 * @typedef t_builtin
 * @brief Entry point of one built-in.
 *
 * @param argc Number of arguments, @c argv[0] being the utility name.
 * @param argv Argument array, expanded words (borrowed, read-only).
 * @param envp Environment of the invocation (borrowed, read-only).
 * @param exit_status Set to the utility's POSIX exit status (borrowed).
 * @return @c ERR_NO or the requalified error (see each built-in).
 */
typedef t_error (*t_builtin)(int argc, char **argv, char **envp, int *exit_status);

// TODO: doc
typedef t_error (*t_special_builtin)(int argc, char **argv, t_runner *runner, int *exit_status);

/* ************************************************************************* */
/*                             SPECIAL BUILT-INS                             */
/* ************************************************************************* */
/* POSIX 2.15: found before PATH search; on error a non-interactive shell
** exits (ERR_BUILTIN -> ERR_POSIX_BUILTIN_SPECIAL in the executor). */

t_error	builtin_break(int argc, char **argv, t_runner *runner, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c : (null utility): does nothing, successfully.
 *
 * Usage: @c ": [argument...]" — the operands are expanded by the shell
 * like any command word, then ignored.
 *
 * @p exit_status always 0.
 * @return @c ERR_NO.
 */
t_error	builtin_colon(int argc, char **argv, t_runner *runner, int *exit_status);

t_error	builtin_continue(int argc, char **argv, t_runner *runner, int *exit_status);
t_error	builtin_dot(int argc, char **argv, t_runner *runner, int *exit_status);
t_error	builtin_eval(int argc, char **argv, t_runner *runner, int *exit_status);
t_error	builtin_exec(int argc, char **argv, t_runner *runner, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c exit: terminates the shell.
 *
 * Usage: @c "exit [n]" — @c n is an unsigned decimal integer. Without
 * @c n the shell exits with the status of the last command executed
 * (@c $?). The status is stored in the parameters and the shell loop is
 * stopped through @c ERR_VEOF, so @c shell_run returns it.
 *
 * Documented choices (POSIX leaves n outside 0-255 undefined):
 * - @c n above 255 (up to @c INT_MAX): taken modulo 256, with an
 *   unspecified-behaviour notice;
 * - @c n not an unsigned decimal integer (signed, non-numeric or
 *   overflowing): diagnosed, the shell still exits with status 2
 *   (bash lane);
 * - more than one operand: diagnosed, the shell does not exit by
 *   itself (special-built-in error lane, POSIX 2.8.1).
 *
 * @p exit_status n when given (modulo 256), else the last command's
 * status; 2 on an invalid @c n; @c ERR_INVALID_USAGE on too many
 * arguments.
 * @return @c ERR_VEOF (shell terminates with @c $?) / @c ERR_BUILTIN /
 *         @c ERR_INTERNAL.
 */
t_error	builtin_exit(int argc, char **argv, t_runner *runner, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c export: marks variables for export, or prints the exported
 *        set.
 *
 * Usage: @c "export -p | name[=word]..." — each @c name gets the export
 * flag, with its value replaced when @c =word is present; @c -p writes
 * the exported variables in a re-input format. Every operand is
 * attempted even after a failure (the last error wins).
 *
 * Documented choices: no argument at all is unspecified (no-op with a
 * notice); mixing @c -p with operands and repeating flags are undefined
 * (XBD 12.1:8, diagnosed).
 *
 * @p exit_status @c ERR_INVALID_USAGE / @c ERR_ASSIGNMENT_MISSING_NAME
 * / @c ERR_VAR_INVALID_NAME / @c ERR_VAR_READ_ONLY / @c ERR_UB /
 * @c ERR_SHELL_NOT_FOUND / @c ERR_POSIX_WRITE / @c ERR_INTERRUPTED /
 * @c ERR_LIBC.
 * @return @c ERR_NO / @c ERR_BUILTIN / @c ERR_INTERRUPTED /
 *         @c ERR_INTERNAL / @c ERR_LIBC.
 */
t_error	builtin_export(int argc, char **argv, t_runner *runner, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c readonly: marks variables read-only, or prints the
 *        read-only set.
 *
 * Usage: @c "readonly -p | name[=word]..." — same shape as
 * @ref builtin_export with the read-only flag: assignments to the
 * marked variables are then rejected (@c ERR_VAR_READ_ONLY). Same
 * documented choices (no argument unspecified, @c -p with operands and
 * repeated flags undefined).
 *
 * @p exit_status same set as @ref builtin_export.
 * @return @c ERR_NO / @c ERR_BUILTIN / @c ERR_INTERRUPTED /
 *         @c ERR_INTERNAL / @c ERR_LIBC.
 */
t_error	builtin_readonly(int argc, char **argv, t_runner *runner, int *exit_status);

t_error	builtin_return(int argc, char **argv, t_runner *runner, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c set: shell options and positional parameters.
 *
 * Usage: @c "set [(-|+)abCefhmnuvx] [(-|+)o [option]] [--] [argument...]"
 * - no argument: writes every shell variable in a re-input format;
 * - @c -x enables an option, @c +x disables it; the short flags map to
 *   allexport(a) notify(b) noclobber(C) errexit(e) noglob(f) cmd
 *   hashing(h) monitor(m) noexec(n) nounset(u) verbose(v) xtrace(x);
 * - @c -o / @c +o take a named option (allexport errexit ignoreeof
 *   monitor noclobber noexec noglob nolog notify nounset pipefail
 *   verbose vi xtrace); without argument the states are printed
 *   (@c -o as a table, @c +o in a re-input format);
 * - remaining operands (or a lone @c -- with none) replace the
 *   positional parameters.
 *
 * Documented choices: a first argument of @c - alone is unspecified
 * (treated as end of options, with a notice); repeated flags are
 * undefined (XBD 12.1:8, diagnosed).
 *
 * @p exit_status @c ERR_INVALID_USAGE / @c ERR_OPT_INVALID_ARG /
 * @c ERR_UB / @c ERR_SHELL_NOT_FOUND / @c ERR_POSIX_WRITE /
 * @c ERR_INTERRUPTED / @c ERR_LIBC.
 * @return @c ERR_NO / @c ERR_BUILTIN / @c ERR_INTERRUPTED /
 *         @c ERR_INTERNAL / @c ERR_LIBC.
 */
t_error	builtin_set(int argc, char **argv, t_runner *runner, int *exit_status);

t_error	builtin_shift(int argc, char **argv, t_runner *runner, int *exit_status);
t_error	builtin_times(int argc, char **argv, t_runner *runner, int *exit_status);
t_error	builtin_trap(int argc, char **argv, t_runner *runner, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c unset: removes variables or functions.
 *
 * Usage: @c "unset [-f|-v] name..." — @c -v (default) unsets variables,
 * @c -f unsets functions. Every operand is attempted even after a
 * failure (the last error wins, each failure printed with the name);
 * unsetting a read-only variable is rejected.
 *
 * Documented choices: no operand is a usage error; giving both @c -f
 * and @c -v is undefined (XBD 12.1:8, diagnosed).
 *
 * @p exit_status @c ERR_INVALID_USAGE / @c ERR_VAR_INVALID_NAME /
 * @c ERR_VAR_READ_ONLY / @c ERR_UB / @c ERR_SHELL_NOT_FOUND /
 * @c ERR_INDEX_OUT_OF_BOUND / @c ERR_LIBC.
 * @return @c ERR_NO / @c ERR_BUILTIN / @c ERR_INTERNAL / @c ERR_LIBC.
 */
t_error	builtin_unset(int argc, char **argv, t_runner *runner, int *exit_status);

/* ************************************************************************* */
/*                            INTRINSIC BUILT-INS                            */
/* ************************************************************************* */
/* Found before PATH search; the shell does not exit on error. */

t_error	builtin_alias(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_bg(int argc, char **argv, char **envp, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c cd: changes the working directory (POSIX ten-step
 *        algorithm).
 *
 * Usage: @c "cd [-L|-P] [-e] [directory | -]"
 * - @c -L (default): logical mode, the curpath is canonicalized
 *   textually (dot and dot-dot resolved against @c PWD, each dot-dot
 *   checked to remove a real directory) and @c PWD keeps the logical
 *   path;
 * - @c -P: physical mode, @c PWD is re-read from @c getcwd after the
 *   change; the last @c -L / @c -P wins;
 * - @c -e: with @c -P, an undeterminable @c PWD after a successful
 *   change becomes an error (otherwise @c PWD keeps the curpath);
 * - no operand: @c HOME (unset or empty @c HOME is a diagnosed error,
 *   bash lane);
 * - @c -: @c OLDPWD, then the new @c PWD is printed;
 * - a relative operand not starting with a dot is searched through
 *   @c CDPATH (empty entry = current directory; a non-empty entry hit
 *   prints the resulting path).
 *
 * @c PWD and @c OLDPWD are updated (exported); a curpath longer than
 * @c PATH_MAX is retried relative to @c PWD. At most one operand.
 *
 * @p exit_status @c ERR_INVALID_USAGE / @c ERR_VAR_NOT_FOUND /
 * @c ERR_VAR_READ_ONLY / @c ERR_SHELL_NOT_FOUND / @c ERR_POSIX_WRITE /
 * @c ERR_INTERRUPTED / @c ERR_LIBC.
 * @return @c ERR_NO / @c ERR_BUILTIN / @c ERR_INTERRUPTED /
 *         @c ERR_INTERNAL.
 */
t_error	builtin_cd(int argc, char **argv, char **envp, int *exit_status);

t_error	builtin_command(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_fc(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_fg(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_getopts(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_hash(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_jobs(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_kill(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_read(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_type(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_ulimit(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_umask(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_unalias(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_wait(int argc, char **argv, char **envp, int *exit_status);

/* ************************************************************************* */
/*                             REGULAR BUILT-INS                             */
/* ************************************************************************* */
/* Found through PATH resolution; the shell does not exit on error. */

/**
 * @ingroup builtins
 * @brief @c echo: writes its operands to standard output.
 *
 * Usage: @c "echo [-neE] [operand...]" — operands are separated by one
 * space and followed by a newline; the whole line is written in a
 * single @c write. POSIX leaves @c -n and backslashes
 * implementation-defined: the bash lane is the documented choice.
 * - @c -n: no trailing newline;
 * - @c -e: decode the XSI escapes @c \\a @c \\b @c \\c @c \\f @c \\n
 *   @c \\r @c \\t @c \\v @c \\\\ and @c \\0num (up to three octal
 *   digits); @c \\c discards everything after it, newline included; an
 *   unknown escape stays literal;
 * - @c -E (default): operands are written as-is.
 * Flags are only recognized in the leading run of arguments made of
 * @c -neE clusters; the last @c e / @c E wins; anything else (@c -,
 * @c -nx, ...) is an operand.
 *
 * @p exit_status @c ERR_POSIX_WRITE / @c ERR_INTERRUPTED / @c ERR_LIBC.
 * @return @c ERR_NO / @c ERR_BUILTIN / @c ERR_INTERRUPTED / @c ERR_LIBC.
 */
t_error	builtin_echo(int argc, char **argv, char **envp, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c env: writes the resulting environment.
 *
 * Usage: @c "env [-i] [name=value]... [utility [argument...]]"
 * - operands up to the first word without @c = override or extend the
 *   environment (base entries keep their position, new names follow in
 *   assignment order, the last assignment of a name wins);
 * - @c -i starts from an empty environment;
 * - a @c utility operand is parsed but not run (@c ERR_NOT_IMPLEMENTED
 *   until the executor is wired, requalified @c ERR_UB).
 *
 * @p exit_status @c ERR_INVALID_USAGE / @c ERR_NOT_IMPLEMENTED (utility
 * operand) / @c ERR_POSIX_WRITE / @c ERR_INTERRUPTED / @c ERR_LIBC.
 * @return @c ERR_NO / @c ERR_BUILTIN / @c ERR_UB / @c ERR_INTERRUPTED /
 *         @c ERR_LIBC.
 */
t_error	builtin_env(int argc, char **argv, char **envp, int *exit_status);

/**
 * @ingroup builtins
 * @brief @c pwd: writes the current working directory.
 *
 * Usage: @c "pwd [-L|-P]" — the last option wins.
 * - @c -L (default): prints @c PWD when it is an absolute pathname
 *   without dot or dot-dot components that names the current directory
 *   (checked by device and inode), otherwise falls back to @c -P;
 * - @c -P: prints the physical path from @c getcwd.
 * POSIX allows no operand: operands are ignored with an
 * unspecified-behaviour notice.
 *
 * @p exit_status @c ERR_INVALID_USAGE / @c ERR_UB /
 * @c ERR_SHELL_NOT_FOUND / @c ERR_POSIX_WRITE / @c ERR_INTERRUPTED /
 * @c ERR_LIBC.
 * @return @c ERR_NO / @c ERR_BUILTIN / @c ERR_INTERRUPTED /
 *         @c ERR_INTERNAL / @c ERR_LIBC.
 */
t_error	builtin_pwd(int argc, char **argv, char **envp, int *exit_status);

#endif
