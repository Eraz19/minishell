#include "ft_getopt_priv.h"

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
		return (ERR_OPT_INVALID);
	i = 0;
	while (valid_flags[i])
	{
		if (valid_flags[i++] == option.flag)
		{
			if (!vector_push(&state->out->options, &option))
				return (ERR_LIBC);
			state->char_i++;
			return (ERR_NO);
		}
	}
	return (ERR_OPT_INVALID);
}

// @ret ERR_OPT_INVALID_ARG / ERR_LIBC
static t_error	getopt_process_flag_optional_arg(
	t_getopt_state *state,
	t_getopt_option *option,
	t_getopt_flag_with_arg *flag_opt)
{
	const char	*arg;
	size_t		i;
	const char	*target_arg;

	arg = state->argv[state->arg_i] + state->char_i;
	state->arg_i++;
	state->char_i = 0;
	if (arg[0] == '\0')
		return (getopt_add_option(state, option));
	i = 0;
	while (flag_opt->arguments_valids[i])
	{
		target_arg = flag_opt->arguments_valids[i];
		if (str_cmp(arg, target_arg) == 0)
		{
			option->argument = target_arg;
			return (getopt_add_option(state, option));
		}
		i++;
	}
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
	t_error	error;

	while (state->argv[state->arg_i][state->char_i] != '\0')
	{
		error = getopt_process_flags_without_arg(state);
		if (error == ERR_LIBC)
			return (error);
		if (error == ERR_OPT_INVALID)
			return (getopt_process_flags_with_arg(state));
	}
	state->arg_i++;
	state->char_i = 0;
	return (ERR_NO);
}
