#include "builtins.h"
#include "set_.h"
#include "params.h"
#include "ft_getopt.h"
# include <stdio.h>

static t_error	set_process_options(int argc, char **argv, t_getopt_out *out)
{
	static const char				*valid_o_args[] = {"allexport", "errexit",
		"ignoreeof", "monitor", "noclobber", "noexec", "noglob", "nolog",
		"notify", "nounset", "pipefail", "verbose", "vi", "xtrace", NULL};
	static t_getopt_flag_with_arg	flags_w_arg[] = {
	{'-', 'o', valid_o_args, true},
	{'+', 'o', valid_o_args, true}
	};
	t_getopt_in						in;

	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == '\0')
		print_unspecified_behaviour("-", "POSIX: set: If the first argument is "
			"'-', the results are unspecified", "treated as end of options");
	in.builtin_name = argv[0];
	in.single_delimiter = true;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "abCefhmnuvx";
	in.valid_plus_flags = "abCefhmnuvx";
	in.options_with_arg = flags_w_arg;
	in.options_with_arg_count = sizeof(flags_w_arg) / sizeof(*flags_w_arg);
	fprintf(stderr, "[%s()] calling ft_getopt()\n", __func__);
	return (ft_getopt(argc, argv, &in, out));
}

static bool	set_has_positionals_request(
				t_getopt_out *out,
				int argc,
				char **argv)
{
	if (out->first_operand_index < (size_t)argc)
		return (true);
	return (out->first_operand_index > 1
		&& str_cmp(argv[out->first_operand_index - 1], "--") == 0);
}

static t_error	set_assign_positionals(size_t first, int argc, char **argv)
{
	t_positionals	positionals;
	t_string		arg;
	size_t			i;
	t_error			err;

	i = first;
	vector_init(&positionals, sizeof(t_string), 0);
	while (i < (size_t)argc)
	{
		if (!string_init(&arg, 0, argv[i], -1))
			return (vector_free(&positionals, string_free_void), error_sys());
		if (!vector_push(&positionals, &arg))
		{
			err = error_sys();
			string_free(&arg);
			return (vector_free(&positionals, string_free_void), err);
		}
		i++;
	}
	err = params_replace_positionals(&positionals);
	if (err.type)
		vector_free(&positionals, string_free_void);
	return (err);
}

static t_error	set_requalify(t_error err, char *builtin_name)
{
	if (err.type)
		err = error_print(err, builtin_name, NULL, NULL);
	if (err.type == ERR_INVALID_USAGE
		|| err.type == ERR_POSIX_WRITE
		|| err.type == ERR_UB
		|| err.type == ERR_OPT_MISSING_ARG
		|| err.type == ERR_INVALID_USAGE)
		err.type = ERR_POSIX_BUILTIN_SPECIAL;
	return (err);
}

t_error	builtin_set(int argc, char **argv, t_runner *runner, int *exit_status)
{
	t_getopt_out	out;
	t_error			err;

	(void)runner;
	if (argc == 1)
		err = params_print(PARAMS_PRINT_SET);
	else
	{
		err = set_process_options(argc, argv, &out);
		fprintf(stderr, "[%s()] set_process_options() returned err == %s\n", __func__, error_to_string(err));
		if (err.type == ERR_NO)
			err = set_apply_options(&out, (size_t)argc, argv);
		if (err.type == ERR_NO
			&& set_has_positionals_request(&out, argc, argv))
			err = set_assign_positionals(out.first_operand_index, argc, argv);
		vector_free(&out.options, NULL);
	}
	*exit_status = (int)err.type;
	return (set_requalify(err, argv[0]));
}
