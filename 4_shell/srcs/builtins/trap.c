#include "builtins.h"
#include "utils.h"
#include "sig.h"
#include "libft.h"

#define TRAP_DEFAULT	1
#define TRAP_IGNORE		2
#define TRAP_CATCH		3

// @ret ERR_INVALID_USAGE / ERR_UB / ERR_LIBC
static inline t_error	trap_process_options(
							int argc,
							char **argv,
							t_getopt_out *out)
{
	t_getopt_in	in;
	t_error		err;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "p";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, out);
	if (err.type)
		return (err);
	return (error(ERR_NO));
}

static inline int	trap_process_mode(char *arg, int *start_index)
{
	int	n;

	if (arg[0] == '\0')
	{
		(*start_index)++;
		return (TRAP_IGNORE);
	}
	else if (ft_isdigit(arg[0]) && parse_int(arg, &n) && n >= 0)
		return (TRAP_DEFAULT);
	else if (str_cmp(arg, "-") == 0)
	{
		(*start_index)++;
		return (TRAP_DEFAULT);
	}
	(*start_index)++;
	return (TRAP_CATCH);
}

static inline t_error	trap_process_err(
							const char *name,
							const char *arg,
							t_error err,
							int *exit_status)
{
	if (err.type == ERR_SIG_WAS_IGNORED_ON_ENTRY)
		return (error(ERR_NO));
	err = error_print(err, name, arg, NULL, NULL);
	if (err.type)
	{
		*exit_status = (int)err.type;
		if (err.type == ERR_VAR_INVALID_NAME)
			err.type = ERR_NO;
	}
	return (err);
}

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC.
static inline t_error	trap_process_operands(
							int argc,
							char **argv,
							size_t first_op_id,
							int *exit_status)
{
	int		mode;
	int		i;
	t_error	err;

	i = (int)first_op_id;
	mode = trap_process_mode(argv[first_op_id], &i);
	while (i < argc)
	{
		if (mode == TRAP_DEFAULT)
			err = sig_set_default(argv[i]);
		else if (mode == TRAP_IGNORE)
			err = sig_set_ignore(argv[i]);
		else
			err = sig_set_trap(argv[i], argv[first_op_id]);
		if (err.type)
		{
			err = trap_process_err(argv[0], argv[i], err, exit_status);
			if (err.type)
				return (err);
		}
		i++;
	}
	return (error(ERR_NO));
}

t_error	builtin_trap(int argc, char **argv, t_runner *runner, int *exit_status)
{
	t_getopt_out	out;
	t_error			err;

	(void)runner;
	*exit_status = 0;
	err = trap_process_options(argc, argv, &out);
	if (err.type == ERR_NO && out.first_operand_index >= (size_t)argc)
	{
		if (out.options.len == 0)
			err = sig_print_all_except_default();
		else
			err = sig_print_all();
	}
	else if (err.type == ERR_NO && out.options.len == 1)
		err = sig_print_conditions(argv[0], argv + out.first_operand_index, exit_status);
	else if (err.type == ERR_NO)
		err = trap_process_operands(argc, argv, out.first_operand_index, exit_status);
	if (err.type && *exit_status == 0)
		*exit_status = (int)err.type;
	vector_free(&out.options, NULL);
	return (err);
}
