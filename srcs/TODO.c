#include "error.h"
#include "token.h"
#include <stdbool.h>
# include <stdio.h>	// DEBUG

/* ---------- TODO: shell ---------- */

t_error		shell_should_interrupt(void)
{
	// TODO
	return (error(ERR_INTERRUPTED));
}

/* ---------- TODO: runner/subshell ---------- */

// Voici les cas possibles
//	- EOI avant cmd_sub closing token.end == -1
//	- cmd_sub closing detected token.end == lexer_i du lexer interne
t_error	runner_find_cmd_sub_closing(t_token *out, t_string *input)
{
	// TODO
	(void)out;
	(void)input;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}

/* ---------- TODO: builtins ---------- */

// Special builtins
int	builtin_break(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}

int	builtin_continue(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_dot(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_eval(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_exec(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_exit(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_return(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_set(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_shift(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_times(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_trap(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}

// Intrinsic builtins

int	builtin_alias(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_bg(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_cd(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_command(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_fc(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_fg(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_getopts(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_hash(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_jobs(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_kill(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_read(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_type(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_ulimit(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_umask(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_unalias(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
int	builtin_wait(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}

// Regular builtins

int	builtin_echo(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}

int	builtin_env(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}

int	builtin_pwd(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return ((int)error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL).type);
}
