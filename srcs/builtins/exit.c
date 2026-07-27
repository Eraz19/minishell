#include "builtins.h"
#include "error.h"
#include "libft.h"
#include "env.h"
#include <signal.h>

#define EXIT_CIT_START	"POSIX: exit: DESCRIPTION: If n is specified and "
#define EXIT_CIT_END_1	" the wait status of the shell or subshell is "
#define EXIT_CIT_END_2	"unspecified."
#define EXIT_CIT_END	EXIT_CIT_END_1 EXIT_CIT_END_2

#define EXIT_NOT_UINT_	"is not an unsigned decimal integer [...]"
#define EXIT_NOT_UINT	EXIT_CIT_START EXIT_NOT_UINT_ EXIT_CIT_END

#define EXIT_256_		"[...] has a value of 256 [...]"
#define EXIT_256		EXIT_CIT_START EXIT_256_ EXIT_CIT_END

#define EXI_GREATER_1	"[...] has a value greater than 256 but not "
#define EXI_GREATER_2	"corresponding to an exit status the shell assigns to "
#define EXI_GREATER_3	"commands terminated by a valid signal,"
#define EXIT_GREATER_	EXI_GREATER_1 EXI_GREATER_2 EXI_GREATER_3
#define EXIT_GREATER	EXIT_CIT_START EXIT_GREATER_ EXIT_CIT_END

#define EXIT_ERR_STATUS	"wait status representing special builtin error"

static inline bool	exit_status_is_signal(int exit_status)
{
	int					signo;
	struct sigaction	sa;

	signo = exit_status - ERR_POSIX_SIGNAL_BASE_CODE;
	return (sigaction(signo, NULL, &sa) == 0);
}

static inline t_error	exit_parse_status(char *arg, int *exit_status)
{
	if (arg[0] == '+'
		|| parse_int(arg, exit_status) == false
		|| *exit_status < 0)
	{
		print_unspecified_behaviour(arg, EXIT_NOT_UINT, EXIT_ERR_STATUS);
		*exit_status = (int)ERR_POSIX_BUILTIN_SPECIAL;
	}
	else if (*exit_status == 256)
	{
		print_unspecified_behaviour(arg, EXIT_256, EXIT_ERR_STATUS);
		*exit_status = (int)ERR_POSIX_BUILTIN_SPECIAL;
	}
	else if (*exit_status > 256 && exit_status_is_signal(*exit_status) == false)
	{
		print_unspecified_behaviour(arg, EXIT_GREATER, EXIT_ERR_STATUS);
		*exit_status %= 256;
	}
	return (error(ERR_EXIT));
}

t_error	builtin_exit(int argc, char **argv, t_runner *runner, int *exit_status)
{
	int		first_operand_index;
	t_error	err;

	(void)runner;
	first_operand_index = 1;
	if (argc > 1 && str_cmp(argv[1], "--") == 0)
		first_operand_index = 2;
	if (first_operand_index >= argc)
	{
		err = env_get_last_status(exit_status);
		if (err.type)
		{
			(void)error_print(err, NULL, NULL);
			*exit_status = (int)err.type;
		}
		return (error(ERR_EXIT_WITH_CURRENT_STATUS));
	}
	else if (argc - first_operand_index > 1)
	{
		err = error_print(error(ERR_INVALID_USAGE), argv[0],
				"too many arguments", NULL, NULL);
		*exit_status = (int)err.type;
		return (error(ERR_EXIT));
	}
	return (exit_parse_status(argv[first_operand_index], exit_status));
}
