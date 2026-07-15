#include "error.h"
#include "libft.h"
#include "params.h"

static bool	exit_parse_status(char *arg, int *status)
{
	if (!ft_isdigit(arg[0]) || !parse_int(arg, status))
		return (false);
	if (*status > 255)
	{
		print_unspecified_behaviour(
			arg, "POSIX: exit: EXIT STATUS: undefined when n is not between"
			" 0 and 255 inclusively", "value taken modulo 256");
		*status %= 256;
	}
	return (true);
}

static t_error	exit_resolve_status(int argc, char **argv, int *status)
{
	if (argc > 2)
		return (error_print(error(ERR_INVALID_USAGE), argv[0],
				"too many arguments", NULL, NULL));
	if (argc == 1)
		return (params_get_last_status(status));
	if (!exit_parse_status(argv[1], status))
		return (error_print(error(ERR_INVALID_USAGE), argv[0], argv[1],
				"not an unsigned decimal integer", NULL, NULL));
	return (error(ERR_NO));
}

t_error	builtin_exit(int argc, char **argv, char **envp, int *exit_status)
{
	t_error	err;

	(void)envp;
	err = exit_resolve_status(argc, argv, exit_status);
	if (err.type == ERR_INVALID_USAGE && argc > 2)
		return (*exit_status = (int)err.type, err.type = ERR_BUILTIN, err);
	if (err.type == ERR_INVALID_USAGE)
		*exit_status = 2;
	else if (err.type)
	{
		*exit_status = (int)err.type;
		err = error_print(err, argv[0], NULL, NULL);
		return (err.type = ERR_INTERNAL, err);
	}
	return (error(ERR_EXIT));
}
