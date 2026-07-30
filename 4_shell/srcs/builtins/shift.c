#include "builtins.h"
#include "env.h"

#define TOO_MANY_ARGS	"too many arguments"
#define NOT_UINT		"is not an unsigned decimal integer"
#define POSIX_CIT		"If the n operand is "
#define POSIX_INVALID	"invalid [...] "
#define POSIX_GREATER	"[...] greater than $# "
#define POSIX_END		"this may be treated as an error"
#define POSIX_IMPL		"special builtin error"

static inline t_error	shift_too_many_args(
							const char *builtin_name,
							int *exit_status)
{
	t_error	err;

	err = error(ERR_INVALID_USAGE);
	err = error_print(err, builtin_name, TOO_MANY_ARGS, NULL, NULL);
	*exit_status = (int)err.type;
	err.type = ERR_POSIX_BUILTIN_SPECIAL;
	return (err);
}

static inline t_error	shift_invalid_arg(
							const char *builtin_name,
							const char *arg,
							int *exit_status)
{
	t_error	err;

	print_unspecified_behaviour(
		builtin_name, POSIX_CIT POSIX_INVALID POSIX_END, POSIX_IMPL);
	err = error(ERR_OPT_INVALID_ARG);
	err = error_print(err, builtin_name, arg, NOT_UINT, NULL, NULL);
	*exit_status = (int)err.type;
	err.type = ERR_POSIX_BUILTIN_SPECIAL;
	return (err);
}

static inline t_error	shift_n(
							const char *name,
							const char *n_arg,
							size_t n,
							int *exit_status)
{
	t_error	err;

	err = env_shift_positionals((size_t)n);
	if (err.type == ERR_NO)
		return (*exit_status = 0, err);
	if (err.type == ERR_SHIFT_INVALID_VALUE)
	{
		print_unspecified_behaviour(
			name, POSIX_CIT POSIX_GREATER POSIX_END, POSIX_IMPL);
		if (n_arg != NULL)
			err = error_print(err, name, n_arg, NULL, NULL);
		else
			err = error_print(err, name, NULL, NULL);
	}
	else
		err = error_print(err, name, NULL, NULL);
	*exit_status = (int)err.type;
	err.type = ERR_POSIX_BUILTIN_SPECIAL;
	return (err);
}

t_error	builtin_shift(int argc, char **argv, t_runner *runner, int *exit_status)
{
	int		first_operand_i;
	int		n;

	(void)runner;
	first_operand_i = 1;
	if (argc > 1 && str_cmp(argv[1], "--") == 0)
		first_operand_i++;
	if (argc - first_operand_i > 1)
		return (shift_too_many_args(argv[0], exit_status));
	else if (first_operand_i >= argc)
		return (shift_n(argv[0], NULL, (size_t)1, exit_status));
	else if (!parse_int(argv[first_operand_i], &n) || n < 0)
		return (shift_invalid_arg(argv[0], argv[first_operand_i], exit_status));
	else if (n == 0)
		return (*exit_status = 0, error(ERR_NO));
	return (shift_n(argv[0], argv[first_operand_i], (size_t)n, exit_status));
}
