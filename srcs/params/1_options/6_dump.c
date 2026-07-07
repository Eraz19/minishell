#include "options.h"
# include <stdio.h>
# include "debug.h"

const char	*option_to_string(t_option option)
{
	if (option == OPT_EXPORT_ALL)
		return ("a");
	else if (option == OPT_NOTIFY)
		return ("b");
	else if (option == OPT_NOCLOBBER)
		return ("C");
	else if (option == OPT_ERREXIT)
		return ("e");
	else if (option == OPT_NOGLOB)
		return ("f");
	else if (option == OPT_HASH_CMDS)
		return ("h");
	else if (option == OPT_INTERACTIVE)
		return ("i");
	else if (option == OPT_MONITOR)
		return ("m");
	else if (option == OPT_NOEXEC)
		return ("n");
	else if (option == OPT_NOUNSET)
		return ("u");
	else if (option == OPT_VERBOSE)
		return ("v");
	else if (option == OPT_XTRACE)
		return ("x");
	else if (option == OPT_CMD_STRING)
		return ("c");
	else if (option == OPT_STDIN_INPUT)
		return ("s");
	else if (option == OPT_IGNOREEOF)
		return ("ignoreeof");
	else if (option == OPT_NOLOG)
		return ("nolog");
	else if (option == OPT_PIPEFAIL)
		return ("pipefail");
	else if (option == OPT_VI)
		return ("vi");
	return ("unknown");
}

void	options_dump(void)
{
	bool			is_active;
	unsigned int	option;
	const char		*name;
	const char		*value;
	t_error			err;

	fprintf(stderr, "\nDUMP OPTIONS\n");
	option = 1u << 0;
	while (option <= OPT_VI)
	{
		name = option_to_string(option);
		err = option_is_active(option, &is_active);
		if (err.type)
			(void)error_print(err, __func__, "option_is_active() failed", NULL, NULL);
		else
		{
			value = bool_to_string(is_active);
			fprintf(stderr, "OPTION %s=%s\n", name, value);
		}
		option <<= 1;
	}
}
