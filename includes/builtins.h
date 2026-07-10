#ifndef BUILTINS_H
# define BUILTINS_H

# include "error.h"
# include <stdbool.h>


// @p exit_status (see each builtin documentation)
// @ret ERR_NO / ERR_BUILTIN / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
typedef t_error (*t_builtin)(int argc, char **argv, char **envp, int *exit_status);

// Special builtins (Shell shall exit on error if invoked directly && non-interactive)

t_error	builtin_break(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_colon(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_continue(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_dot(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_eval(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_exec(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_exit(int argc, char **argv, char **envp, int *exit_status);

// @p exit_status ERR_INVALID_USAGE / ERR_ASSIGNMENT_MISSING_NAME
// 					/ ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_UB
// 					/ ERR_SHELL_NOT_FOUND / ERR_POSIX_WRITE
// 					/ ERR_INTERRUPTED / ERR_LIBC
// @ret ERR_NO / ERR_BUILTIN / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	builtin_export(int argc, char **argv, char **envp, int *exit_status);

// @p exit_status ERR_INVALID_USAGE / ERR_ASSIGNMENT_MISSING_NAME
// 					/ ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_UB
// 					/ ERR_SHELL_NOT_FOUND / ERR_POSIX_WRITE
// 					/ ERR_INTERRUPTED / ERR_LIBC
// @ret ERR_NO / ERR_BUILTIN / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	builtin_readonly(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_return(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_set(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_shift(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_times(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_trap(int argc, char **argv, char **envp, int *exit_status);

// @p exit_status ERR_INVALID_USAGE / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY
// 					/ ERR_UB / ERR_SHELL_NOT_FOUND / ERR_INDEX_OUT_OF_BOUND / ERR_LIBC
// @ret ERR_NO / ERR_BUILTIN / ERR_INTERNAL / ERR_LIBC
t_error	builtin_unset(int argc, char **argv, char **envp, int *exit_status);

// Intrinsic builtins (Shell shall not exit on error)

t_error	builtin_alias(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_bg(int argc, char **argv, char **envp, int *exit_status);
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

// Regular builtins (Shell shall not exit on error)

t_error	builtin_echo(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_env(int argc, char **argv, char **envp, int *exit_status);
t_error	builtin_pwd(int argc, char **argv, char **envp, int *exit_status);

#endif
