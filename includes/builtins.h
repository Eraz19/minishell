#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

typedef int (*t_builtin)(int argc, char **argv, char **envp);

// Special builtins (Shell shall exit on error if invoked directly && non-interactive)

int	builtin_break(int argc, char **argv, char **envp);
int	builtin_colon(int argc, char **argv, char **envp);
int	builtin_continue(int argc, char **argv, char **envp);
int	builtin_dot(int argc, char **argv, char **envp);
int	builtin_eval(int argc, char **argv, char **envp);
int	builtin_exec(int argc, char **argv, char **envp);
int	builtin_exit(int argc, char **argv, char **envp);
int	builtin_export(int argc, char **argv, char **envp);
int	builtin_readonly(int argc, char **argv, char **envp);
int	builtin_return(int argc, char **argv, char **envp);
int	builtin_set(int argc, char **argv, char **envp);
int	builtin_shift(int argc, char **argv, char **envp);
int	builtin_times(int argc, char **argv, char **envp);
int	builtin_trap(int argc, char **argv, char **envp);
int	builtin_unset(int argc, char **argv, char **envp);

// Intrinsic builtins (Shell shall not exit on error)

int	builtin_alias(int argc, char **argv, char **envp);
int	builtin_bg(int argc, char **argv, char **envp);
int	builtin_cd(int argc, char **argv, char **envp);
int	builtin_command(int argc, char **argv, char **envp);
int	builtin_fc(int argc, char **argv, char **envp);
int	builtin_fg(int argc, char **argv, char **envp);
int	builtin_getopts(int argc, char **argv, char **envp);
int	builtin_hash(int argc, char **argv, char **envp);
int	builtin_jobs(int argc, char **argv, char **envp);
int	builtin_kill(int argc, char **argv, char **envp);
int	builtin_read(int argc, char **argv, char **envp);
int	builtin_type(int argc, char **argv, char **envp);
int	builtin_ulimit(int argc, char **argv, char **envp);
int	builtin_umask(int argc, char **argv, char **envp);
int	builtin_unalias(int argc, char **argv, char **envp);
int	builtin_wait(int argc, char **argv, char **envp);

// Regular builtins (Shell shall not exit on error)

int	builtin_echo(int argc, char **argv, char **envp);
int	builtin_env(int argc, char **argv, char **envp);
int	builtin_pwd(int argc, char **argv, char **envp);

#endif
