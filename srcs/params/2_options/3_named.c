#include "libft.h"
#include "error.h"
#include "options.h"
#include <stddef.h>

static bool	option_equals(const char *arg, const char *name)
{
	size_t	len;
	size_t	i;

	len = str_len(name);
	i = 0;
	while (i < len)
	{
		if (arg[i] != name[i])
			return (false);
		i++;
	}
	return (arg[i] == '\0');
}

static bool	options_process_name1(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m)
{
	if (option_equals(arg, "allexport"))
		option_set(options, OPT_EXPORT_ALL, on);
	else if (option_equals(arg, "errexit"))
		option_set(options, OPT_ERREXIT, on);
	else if (option_equals(arg, "monitor"))
	{
		option_set(options, OPT_MONITOR, on);
		*explicit_plus_m = !on;
	}
	else if (option_equals(arg, "noclobber"))
		option_set(options, OPT_NOCLOBBER, on);
	else if (option_equals(arg, "noglob"))
		option_set(options, OPT_NOGLOB, on);
	else if (option_equals(arg, "noexec"))
		option_set(options, OPT_NOEXEC, on);
	else if (option_equals(arg, "notify"))
		option_set(options, OPT_NOTIFY, on);
	else
		return (false);
	return (true);
}

static bool	options_process_name2(t_option *options, const char *arg, bool on)
{
	if (option_equals(arg, "nounset"))
		option_set(options, OPT_NOUNSET, on);
	else if (option_equals(arg, "verbose"))
		option_set(options, OPT_VERBOSE, on);
	else if (option_equals(arg, "xtrace"))
		option_set(options, OPT_XTRACE, on);
	else if (option_equals(arg, "ignoreeof"))
		option_set(options, OPT_IGNOREEOF, on);
	else if (option_equals(arg, "nolog"))
		option_set(options, OPT_NOLOG, on);
	else if (option_equals(arg, "pipefail"))
		option_set(options, OPT_PIPEFAIL, on);
	else if (option_equals(arg, "vi"))
		option_set(options, OPT_VI, on);
	else
		return (false);
	return (true);
}

bool	options_process_name(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m)
{
	if (!arg)
	{
		error_print("-o / +o", "needs an argument", ERR_OPTION_INVALID);
		// TODO: print LA TETE A XAVIER (undefined)
		return (false);
	}
	if (options_process_name1(options, arg, on, explicit_plus_m))
		return (true);
	if (options_process_name2(options, arg, on))
		return (true);
	error_print(NULL, arg, ERR_OPTION_INVALID);
	return (false);
}
