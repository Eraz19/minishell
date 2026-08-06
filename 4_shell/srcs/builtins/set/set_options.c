/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:41:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:55:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "set_.h"
#include "env.h"
#include "ft_getopt.h"

bool	set_named_option(size_t i, const char **name, t_option *bit)
{
	static const char		*names[] = {"allexport", "errexit", "ignoreeof",
		"monitor", "noclobber", "noexec", "noglob", "nolog", "notify",
		"nounset", "pipefail", "verbose", "vi", "xtrace"};
	static const t_option	bits[] = {OPT_EXPORT_ALL, OPT_ERREXIT,
		OPT_IGNOREEOF, OPT_MONITOR, OPT_NOCLOBBER, OPT_NOEXEC, OPT_NOGLOB,
		OPT_NOLOG, OPT_NOTIFY, OPT_NOUNSET, OPT_PIPEFAIL, OPT_VERBOSE,
		OPT_VI, OPT_XTRACE};

	if (i >= sizeof(bits) / sizeof(*bits))
		return (false);
	*name = names[i];
	*bit = bits[i];
	return (true);
}

static t_error	set_option_bit(const t_getopt_option *opt, t_option *bit)
{
	size_t					i;
	const char				*name;
	static const char		*flags = "abCefhmnuvx";
	static const t_option	flag_bits[] = {OPT_EXPORT_ALL, OPT_NOTIFY,
		OPT_NOCLOBBER, OPT_ERREXIT, OPT_NOGLOB, OPT_CMD_HASH, OPT_MONITOR,
		OPT_NOEXEC, OPT_NOUNSET, OPT_VERBOSE, OPT_XTRACE};

	if (opt->argument == NULL)
		return (*bit = flag_bits[str_chr(flags, opt->flag) - flags],
			error(ERR_NO));
	i = 0;
	while (set_named_option(i, &name, bit))
	{
		if (str_cmp(name, opt->argument) == 0)
			return (error(ERR_NO));
		i++;
	}
	return (error(ERR_OPT_INVALID_ARG));
}

t_error	handle_set_o_option(
			t_getopt_option opt,
			t_getopt_out *out,
			size_t argc,
			char **argv)
{
	if (out->options.len > 1)
		return (error_print(
				error(ERR_OPT_MISSING_ARG), argv[0], "o", NULL, NULL));
	if (out->first_operand_index < argc)
		return (error_print(
				error(ERR_INVALID_USAGE), argv[0],
				SET_USAGE_1, SET_USAGE_2, SET_USAGE_3, SET_USAGE_4, SET_USAGE_5,
				NULL, NULL));
	return (set_print_options(opt.sign));
}

t_error	set_apply_options(t_getopt_out *out, size_t argc, char **argv)
{
	size_t			i;
	t_getopt_option	opt;
	t_option		bit;
	t_error			err;

	i = 0;
	err = error(ERR_NO);
	while (i < out->options.len)
	{
		opt = ((t_getopt_option *)out->options.data)[i];
		if (opt.flag == 'o' && opt.argument == NULL)
			err = handle_set_o_option(opt, out, argc, argv);
		else
		{
			err = set_option_bit(&opt, &bit);
			if (err.type == ERR_NO)
				err = env_set_option(bit, opt.sign == '-');
		}
		if (err.type)
			return (err);
		i++;
	}
	return (err);
}
