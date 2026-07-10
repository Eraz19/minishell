#include <unistd.h>
#include "set_.h"
#include "params.h"
#include "posix_helpers.h"

static bool	set_named_option(size_t i, const char **name, t_option *bit)
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
	static const char		*flags = "abCefhmnuvx";
	static const t_option	flag_bits[] = {OPT_EXPORT_ALL, OPT_NOTIFY,
		OPT_NOCLOBBER, OPT_ERREXIT, OPT_NOGLOB, OPT_CMD_HASH, OPT_MONITOR,
		OPT_NOEXEC, OPT_NOUNSET, OPT_VERBOSE, OPT_XTRACE};
	const char				*name;

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

static t_error	set_print_one(char sign, const char *name, bool on)
{
	t_error		err;
	t_string	line;
	const char	*prefix;
	const char	*sufix;

	if (sign == '-')
	{
		sufix = "\ton\n";
		if (!on)
			sufix = "\toff\n";
		prefix = "";
	}
	else
	{
		prefix = "set -o ";
		if (!on)
			prefix = "set +o ";
		sufix = "\n";
	}
	if (!string_init(&line, 0, prefix, -1))
		return (error_sys());
	if (!string_append_n(&line, name, -1) || !string_append_n(&line, sufix, -1))
		return (err = error_sys(), string_free(&line), err);
	err = posix_write(STDOUT_FILENO, line.data, line.len);
	return (string_free(&line), err);
}

static t_error	set_print_options(char sign)
{
	size_t		i;
	bool		on;
	t_option	bit;
	t_error		err;
	const char	*name;

	i = 0;
	while (set_named_option(i, &name, &bit))
	{
		err = option_is_active(bit, &on);
		if (err.type)
			return (err);
		err = set_print_one(sign, name, on);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

t_error	set_apply_options(t_getopt_out *out)
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
			err = set_print_options(opt.sign);
		else
		{
			err = set_option_bit(&opt, &bit);
			if (err.type == ERR_NO)
				err = params_set_option(bit, opt.sign == '-');
		}
		if (err.type)
			return (err);
		i++;
	}
	return (err);
}
