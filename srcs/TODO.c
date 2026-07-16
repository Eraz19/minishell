#include "error.h"
#include "scanner.h"
#include <stdbool.h>
# include <stdio.h>	// DEBUG

t_error	scanner_cmd_sub_init(const t_scanner *main_scanner, t_scanner *cmd_sub_scanner)
{
	(void)main_scanner;
	(void)cmd_sub_scanner;
	return (error(ERR_NO));
}

void	scanner_cmd_sub_free(t_scanner *cmd_sub_scanner)
{
	(void)cmd_sub_scanner;
}


/* ---------- TODO: shell ---------- */

t_error		shell_should_interrupt(void)
{
	// TODO
	return (error(ERR_INTERRUPTED));
}

/* ---------- TODO: builtins ---------- */

// Special builtins
t_error	builtin_break(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}

t_error	builtin_continue(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_dot(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_eval(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_exec(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}

t_error	builtin_return(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_shift(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_times(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_trap(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}

// Intrinsic builtins

t_error	builtin_bg(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_command(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_fc(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_fg(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_getopts(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_hash(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_jobs(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_kill(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_read(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_type(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_ulimit(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_umask(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}
t_error	builtin_wait(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	(void)exit_status;
	return (error_print(error(ERR_NOT_IMPLEMENTED), __func__, NULL, NULL));
}

// Regular builtins

