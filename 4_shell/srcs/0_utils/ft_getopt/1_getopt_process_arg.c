#include "ft_getopt_priv.h"
# include <stdio.h>

// @ret ERR_OPT_INVALID / ERR_LIBC
static t_error	getopt_process_flags_without_arg(t_getopt_state *state)
{
	t_getopt_option option;
	const char		*valid_flags;
	size_t			i;

	option.sign = state->argv[state->arg_i][0];
	option.flag = state->argv[state->arg_i][state->char_i];
	option.argument = NULL;
	if (option.sign == '-')
		valid_flags = state->in->valid_minus_flags;
	else
		valid_flags = state->in->valid_plus_flags;
	if (!valid_flags)
		return (error(ERR_OPT_INVALID));
	i = 0;
	while (valid_flags[i])
	{
		if (valid_flags[i++] == option.flag)
		{
			if (!vector_push(&state->out->options, &option))
				return (error_sys());
			state->char_i++;
			return (error(ERR_NO));
		}
	}
	return (error(ERR_OPT_INVALID));
}

// @ret ERR_OPT_INVALID_ARG / ERR_LIBC
// A detached argument (next argv) is consumed only when it matches the
// valid list; anything else stays an operand and the option is bare.
static t_error	getopt_process_flag_optional_arg(
	t_getopt_state *state,
	t_getopt_option *option,
	t_getopt_flag_with_arg *flag_opt)
{
	const char	*arg;
	size_t		i;
	bool		detached;

	arg = state->argv[state->arg_i] + state->char_i;
	state->arg_i++;
	state->char_i = 0;
	detached = (arg[0] == '\0' && state->argv[state->arg_i] != NULL);
	if (detached)
		arg = state->argv[state->arg_i];
	i = 0;
	while (arg[0] != '\0' && flag_opt->arguments_valids[i])
	{
		if (str_cmp(arg, flag_opt->arguments_valids[i]) == 0)
		{
			option->argument = flag_opt->arguments_valids[i];
			state->arg_i += detached;
			return (getopt_add_option(state, option));
		}
		i++;
	}
	if (arg[0] == '\0' || detached)
		return (getopt_add_option(state, option));
	return (getopt_err(state, option->flag, arg, ERR_OPT_INVALID_ARG));
}

// @ret ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
static t_error	getopt_process_flag_mandatory_arg(
	t_getopt_state *state,
	t_getopt_option *option,
	t_getopt_flag_with_arg *flag_opt)
{
	const char	*arg;
	size_t		i;

	if (state->argv[state->arg_i][state->char_i] != '\0')
		arg = state->argv[state->arg_i] + state->char_i;
	else
	{
		state->arg_i++;
		if (state->arg_i >= state->argc)
			return (getopt_err(state, option->flag, NULL, ERR_OPT_MISSING_ARG));
		arg = state->argv[state->arg_i];
	}
	state->arg_i++;
	state->char_i = 0;
	i = 0;
	while (flag_opt->arguments_valids[i])
	{
		option->argument = flag_opt->arguments_valids[i];
		if (str_cmp(arg, option->argument) == 0)
			return (getopt_add_option(state, option));
		i++;
	}
	return (getopt_err(state, option->flag, arg, ERR_OPT_INVALID_ARG));
}

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
static t_error	getopt_process_flags_with_arg(t_getopt_state *state)
{
	t_getopt_option			option;
	t_getopt_flag_with_arg	*curr;
	size_t					i;

	option.sign = state->argv[state->arg_i][0];
	option.flag = state->argv[state->arg_i][state->char_i];
	option.argument = NULL;
	i = 0;
	fprintf(stderr, "[%s()] options_with_arg_count=%zu\n", __func__, state->in->options_with_arg_count);
	while (i < state->in->options_with_arg_count)
	{
		curr = &state->in->options_with_arg[i++];
		if (option.sign != curr->sign)
			continue ;
		if (curr->flag == option.flag)
		{
			state->char_i++;
			if (curr->arguments_are_optional)
				return (getopt_process_flag_optional_arg(state, &option, curr));
			return (getopt_process_flag_mandatory_arg(state, &option, curr));
		}
	}
	return (getopt_err(state, option.flag, NULL, ERR_OPT_INVALID));
}

t_error	getopt_process_arg(t_getopt_state *state)
{
	t_error	err;

	while (state->argv[state->arg_i][state->char_i] != '\0')
	{
		err = getopt_process_flags_without_arg(state);
		if (err.type == ERR_LIBC)
			return (err);
		if (err.type == ERR_OPT_INVALID)
			return (getopt_process_flags_with_arg(state));
	}
	state->arg_i++;
	state->char_i = 0;
	return (error(ERR_NO));
}
