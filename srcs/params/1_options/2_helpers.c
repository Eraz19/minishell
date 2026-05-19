#include "shell.h"
#include <stdlib.h>
# include "logs.h"	// TODO: tmp debug

bool	option_is_active(t_option option)
{
	t_shell	*shell;

	shell = shell_get();
	return ((shell->params.options & option) != 0);
}

bool	option_is_active_in(t_option options, t_option option)
{
	return ((options & option) != 0);
}

void	option_set(t_option *options, t_option option, bool on)
{
	if (on)
		print_pass("Setting ON  option %s\n", option_to_string(option));
	else
		print_pass("Setting OFF option %s\n", option_to_string(option));
	if (on)
		*options |= option;
	else
		*options &= ~option;
}

static void	options_add_to_string(t_option options, char **dst, size_t *i_ptr)
{
	size_t	i;

	i = *i_ptr;
	if (option_is_active_in(options, OPT_MONITOR))
		(*dst)[i++] = 'm';
	if (option_is_active_in(options, OPT_NOEXEC))
		(*dst)[i++] = 'n';
	if (option_is_active_in(options, OPT_NOUNSET))
		(*dst)[i++] = 'u';
	if (option_is_active_in(options, OPT_VERBOSE))
		(*dst)[i++] = 'v';
	if (option_is_active_in(options, OPT_XTRACE))
		(*dst)[i++] = 'x';
	if (option_is_active_in(options, OPT_CMD_STRING))
		(*dst)[i++] = 'c';
	if (option_is_active_in(options, OPT_STDIN_INPUT))
		(*dst)[i++] = 's';
	*i_ptr = i;
}

t_error	options_get(t_option options, char **dst)
{
	size_t	i;

	*dst = malloc(OPT_SINGLE_COUNT + 1);
	if (!*dst)
		return (ERR_LIBC);
	i = 0;
	if (option_is_active_in(options, OPT_EXPORT_ALL))
		(*dst)[i++] = 'a';
	if (option_is_active_in(options, OPT_NOTIFY))
		(*dst)[i++] = 'b';
	if (option_is_active_in(options, OPT_NOCLOBBER))
		(*dst)[i++] = 'C';
	if (option_is_active_in(options, OPT_ERREXIT))
		(*dst)[i++] = 'e';
	if (option_is_active_in(options, OPT_NOGLOB))
		(*dst)[i++] = 'f';
	if (option_is_active_in(options, OPT_HASHALL))
		(*dst)[i++] = 'h';
	if (option_is_active_in(options, OPT_INTERACTIVE))
		(*dst)[i++] = 'i';
	options_add_to_string(options, dst, &i);
	(*dst)[i] = '\0';
	return (ERR_NO);
}
