#include "builtins.h"
#include "libft.h"
#include "params.h"

static inline t_error	builtin_wait_one(char *name, char *arg, int *status)
{
	pid_t	pid;
	t_error	err;

	if (ft_isdigit(arg[0]) == false || parse_int(arg, &pid) == false)
		return (error_print(error(ERR_PID_INVALID), name, arg, NULL, NULL));
	err = params_wait(pid, status);
	if (err.type && err.type != ERR_INTERRUPTED)
		return (error_print(err, name, arg, NULL, NULL));
	return (err);
}

static inline t_error	builtin_wait_n(
							int argc,
							char **argv,
							int first_operand_index,
							int *exit_status)
{
	int		i;
	t_error	last_err;
	t_error	err;

	i = first_operand_index;
	err.type = ERR_NO;
	while (i < argc)
	{
		last_err = builtin_wait_one(argv[0], argv[i], exit_status);
		if (last_err.type == ERR_INTERRUPTED)
			return (error(ERR_NO));
		err = error_priorize(err, last_err);
		i++;
	}
	return (err);
}

static inline t_error	builtin_wait_all(const char *name, int *exit_status)
{
	t_error	err;

	err = params_wait_all(exit_status);
	if (err.type == ERR_INTERRUPTED)
		err.type = ERR_NO;
	if (err.type)
		return (error_print(err, name, NULL, NULL));
	return (err);
}

t_error	builtin_wait(int argc, char **argv, char **envp, int *exit_status)
{
	int		first_operand_index;

	(void)envp;
	first_operand_index = 1;
	if (argc > 1 && str_cmp(argv[1], "--") == 0)
		first_operand_index = 2;
	if (first_operand_index >= argc)
		return (builtin_wait_all(argv[0], exit_status));
	return (builtin_wait_n(argc, argv, first_operand_index, exit_status));
}
