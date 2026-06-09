#include "options_priv.h"
#include "ft_getopt.h"
#include "logs.h"
#include <unistd.h>

static void	options_build_getopt_in(t_getopt_in *in)
{
	static const char				*valid_flags = "abCefhimnuvxcs";
	static const char				*valid_o_args[] = {
		"allexport", "errexit", "monitor", "noclobber", "noglob", "noexec",
		"notify", "nounset", "verbose", "xtrace", "ignoreeof", "nolog",
		"pipefail", "vi", NULL};
	static t_getopt_flag_with_arg	flags_w_arg[] = {
	{'-', 'o', valid_o_args, false},
	{'+', 'o', valid_o_args, false}
	};

	in->builtin_name = "sh";
	in->ub_on_repeated_flags = true;
	in->single_delimiter = true;
	in->valid_minus_flags = valid_flags;
	in->valid_plus_flags = valid_flags;
	in->options_with_arg = flags_w_arg;
	in->options_with_arg_count = sizeof(flags_w_arg) / sizeof(*flags_w_arg);
}

// @ret ERR_OPT_INVALID
static t_error	options_apply_getopt_out(
	t_option *options,
	t_getopt_out *out,
	bool *explicit_plus_m)
{
	t_getopt_option	option;
	size_t			i;
	t_error			error;

	i = 0;
	while (i < out->options.len)
	{
		option = ((t_getopt_option *)out->options.data)[i];
		if (!option.argument)
			error = options_process_flag(
				options, option.flag, option.sign == '-', explicit_plus_m);
		else
			error = options_process_name(
				options, option.argument, option.sign == '-', explicit_plus_m);
		if (error != ERR_NO)
			return (error);
		i++;
	}
	return (ERR_NO);
}

static void	options_finalize(
	t_option *options,
	size_t remaining_args,
	bool explicit_plus_m)
{
	if (!option_is_active_in(*options, OPT_CMD_STRING) && remaining_args == 0)
		option_set(options, OPT_STDIN_INPUT, true);
	if (option_is_active_in(*options, OPT_STDIN_INPUT)
		&& isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		option_set(options, OPT_INTERACTIVE, true);
	if (option_is_active_in(*options, OPT_INTERACTIVE) && !explicit_plus_m)
		option_set(options, OPT_MONITOR, true);
}

t_error	options_load(
	t_option *options,
	int argc,
	char **argv,
	size_t *start_index)
{
	t_getopt_in		in;
	t_getopt_out	out;
	bool			explicit_plus_m;
	size_t			remaining_args;
	t_error			error;

	print_title("options_load()");
	*options = 0u;
	explicit_plus_m = false;
	options_build_getopt_in(&in);
	error = ft_getopt(argc, argv, &in, &out);
	if (error != ERR_NO)
		return (error);
	error = options_apply_getopt_out(options, &out, &explicit_plus_m);
	vector_free(&out.options, NULL);
	if (error != ERR_NO)
		return (error);
	*start_index = out.first_operand_index;
	print_result("options_load()");
	print_title("options_finalize()");
	if (*start_index >= (size_t)argc)
		remaining_args = 0;
	else
		remaining_args = (size_t)argc - *start_index;
	options_finalize(options, remaining_args, explicit_plus_m);
	print_result("options_finalize()");
	return (ERR_NO);
}
