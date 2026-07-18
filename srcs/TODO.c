#include "error.h"
#include <stdbool.h>
# include <stdio.h>	// DEBUG

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
	/*
	(use shell_is_subshell())
	if trap sans opérande && in_subshell && !trap_table_modified_since_subshell_entry:
		print saved_traps_on_subshell_entry
	else:
		print current_traps
	*/
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

