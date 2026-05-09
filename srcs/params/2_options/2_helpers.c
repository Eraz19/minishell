#include "options.h"
#include <stdlib.h>

/* ---------------------------- TODO: TMP DEBUG ----------------------------- */
# include <stdio.h>	// TODO: tmp debug

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
	else if (option == OPT_HASHALL)
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
/* -------------------------------------------------------------------------- */

bool	option_is_active(t_option options, t_option option)
{
	return ((options & option) != 0);
}

void	option_set(t_option *options, t_option option, bool on)
{
	if (on)
		printf("Setting ON  option %s\n", option_to_string(option));
	else
		printf("Setting OFF option %s\n", option_to_string(option));
	if (on)
		*options |= option;
	else
		*options &= ~option;
}

static void	options_add_to_string(t_option options, char **dst, size_t *i_ptr)
{
	size_t	i;

	i = *i_ptr;
	if (option_is_active(options, OPT_MONITOR))
		(*dst)[i++] = 'm';
	if (option_is_active(options, OPT_NOEXEC))
		(*dst)[i++] = 'n';
	if (option_is_active(options, OPT_NOUNSET))
		(*dst)[i++] = 'u';
	if (option_is_active(options, OPT_VERBOSE))
		(*dst)[i++] = 'v';
	if (option_is_active(options, OPT_XTRACE))
		(*dst)[i++] = 'x';
	if (option_is_active(options, OPT_CMD_STRING))
		(*dst)[i++] = 'c';
	if (option_is_active(options, OPT_STDIN_INPUT))
		(*dst)[i++] = 's';
	*i_ptr = i;
}

t_error	options_to_string(t_option options, char **dst)
{
	size_t	i;

	*dst = malloc(OPT_SINGLE_COUNT + 1);
	if (!*dst)
		return (ERR_LIBC);
	i = 0;
	if (option_is_active(options, OPT_EXPORT_ALL))
		(*dst)[i++] = 'a';
	if (option_is_active(options, OPT_NOTIFY))
		(*dst)[i++] = 'b';
	if (option_is_active(options, OPT_NOCLOBBER))
		(*dst)[i++] = 'C';
	if (option_is_active(options, OPT_ERREXIT))
		(*dst)[i++] = 'e';
	if (option_is_active(options, OPT_NOGLOB))
		(*dst)[i++] = 'f';
	if (option_is_active(options, OPT_HASHALL))
		(*dst)[i++] = 'h';
	if (option_is_active(options, OPT_INTERACTIVE))
		(*dst)[i++] = 'i';
	options_add_to_string(options, dst, &i);
	(*dst)[i] = '\0';
	return (ERR_NO);
}
