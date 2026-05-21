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

static t_error	getopt_process(t_getopt_state *state)
{
	t_error		error;

	while (state->arg_i < state->argc)
	{
		if (getopt_is_delimiter(state))
			break ;
		state->char_i = 1;
		error = getopt_process_arg(state);
		if (error != ERR_NO)
			return (error);
	}
	state->out->first_operand_index = (size_t)state->arg_i;
	return (ERR_NO);
}

static void	getopt_catch_ub(t_getopt_out *out)
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
				undefined_behaviour("POSIX (XBD 12.1-3): "
					"If an option that does not have option-arguments is "
					"repeated, the results are undefined");
		}
	}
}

t_error	ft_getopt(int argc, char **argv, t_getopt_in *in, t_getopt_out *out)
{
	t_getopt_state	state;
	t_error			error;

	state.argc = argc;
	state.argv = argv;
	state.arg_i = 1;
	state.char_i = 0;
	state.in = in;
	state.out = out;
	(void)vector_init(&out->options, sizeof(t_getopt_option), 0);
	out->first_operand_index = 1;
	error = getopt_process(&state);
	if (error != ERR_NO)
		return (error);
	if (in->ub_on_repeated_flags)
		getopt_catch_ub(out);
	return (ERR_NO);
}
