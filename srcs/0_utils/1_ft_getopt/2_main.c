#include "ft_getopt_priv.h"

static bool	getopt_is_delimiter(t_getopt_state *state)
{
	const char	*arg;

	arg = state->argv[state->arg_i];
	if (str_cmp(arg, "-") == 0)
	{
		if (state->in->single_delimiter == true)
			state->arg_i++;
		return (true);
	}
	if (str_cmp(arg, "--") == 0)
	{
		state->arg_i++;
		return (true);
	}
	if ((arg[0] != '-' && arg[0] != '+') || str_cmp(arg, "+") == 0)
		return (true);
	return (false);
}

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
static t_error	getopt_process(t_getopt_state *state)
{
	t_error		err;

	while (state->arg_i < state->argc)
	{
		if (getopt_is_delimiter(state))
			break ;
		state->char_i = 1;
		err = getopt_process_arg(state);
		if (err.type != ERR_NO)
			return (err);
	}
	state->out->first_operand_index = (size_t)state->arg_i;
	return (error(ERR_NO));
}

static t_error	getopt_catch_ub(t_getopt_out *out)
{
	size_t			i;
	t_getopt_option	*a;
	t_getopt_option	*b;
	size_t			j;

	i = 0;
	while (i < out->options.len)
	{
		a = &((t_getopt_option *)out->options.data)[i++];
		if (a->argument)
			continue ;
		j = i;
		while (j < out->options.len)
		{
			b = &((t_getopt_option *)out->options.data)[j++];
			if (b->argument)
				continue ;
			if (a->sign == b->sign && a->flag == b->flag)
				return (vector_free(&out->options, NULL),
							undefined_behaviour("POSIX (XBD 12.1-3): "
								"If an option that does not have option-argum"
								"ents is repeated, the results are undefined"));
		}
	}
	return (error(ERR_NO));
}

t_error	ft_getopt(int argc, char **argv, t_getopt_in *in, t_getopt_out *out)
{
	t_getopt_state	state;
	t_error			err;

	state.argc = argc;
	state.argv = argv;
	state.arg_i = 1;
	state.char_i = 0;
	state.in = in;
	state.out = out;
	(void)vector_init(&out->options, sizeof(t_getopt_option), 0);
	out->first_operand_index = 1;
	err = getopt_process(&state);
	if (err.type == ERR_LIBC)
		err = error_print(err, in->builtin_name,
				"arguments parsing failed", NULL, NULL);
	if (err.type)
		return (vector_free(&out->options, NULL), err);
	if (in->ub_on_repeated_flags)
		return (getopt_catch_ub(out));
	return (error(ERR_NO));
}
