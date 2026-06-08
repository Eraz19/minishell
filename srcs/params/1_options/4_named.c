#include "libft.h"
#include "options.h"

static bool	options_process_name1(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m)
{
	if (str_cmp(arg, "allexport") == 0)
		option_set(options, OPT_EXPORT_ALL, on);
	else if (str_cmp(arg, "errexit") == 0)
		option_set(options, OPT_ERREXIT, on);
	else if (str_cmp(arg, "monitor") == 0)
	{
		option_set(options, OPT_MONITOR, on);
		*explicit_plus_m = !on;
	}
	else if (str_cmp(arg, "noclobber") == 0)
		option_set(options, OPT_NOCLOBBER, on);
	else if (str_cmp(arg, "noglob") == 0)
		option_set(options, OPT_NOGLOB, on);
	else if (str_cmp(arg, "noexec") == 0)
		option_set(options, OPT_NOEXEC, on);
	else if (str_cmp(arg, "notify") == 0)
		option_set(options, OPT_NOTIFY, on);
	else
		return (false);
	return (true);
}

static bool	options_process_name2(t_option *options, const char *arg, bool on)
{
	if (str_cmp(arg, "nounset") == 0)
		option_set(options, OPT_NOUNSET, on);
	else if (str_cmp(arg, "verbose") == 0)
		option_set(options, OPT_VERBOSE, on);
	else if (str_cmp(arg, "xtrace") == 0)
		option_set(options, OPT_XTRACE, on);
	else if (str_cmp(arg, "ignoreeof") == 0)
		option_set(options, OPT_IGNOREEOF, on);
	else if (str_cmp(arg, "nolog") == 0)
		option_set(options, OPT_NOLOG, on);
	else if (str_cmp(arg, "pipefail") == 0)
		option_set(options, OPT_PIPEFAIL, on);
	else if (str_cmp(arg, "vi") == 0)
		option_set(options, OPT_VI, on);
	else
		return (false);
	return (true);
}

t_error	options_process_name(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m)
{
	if (options_process_name1(options, arg, on, explicit_plus_m))
		return (ERR_NO);
	if (options_process_name2(options, arg, on))
		return (ERR_NO);
	error_print(NULL, arg, ERR_OPT_INVALID_ARG);
	return (ERR_OPT_INVALID_ARG);
}
