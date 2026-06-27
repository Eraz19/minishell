#include "shell.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

t_error	option_is_active(t_option option, bool *out)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	*out = (params->options & option) != 0;
	return (error(ERR_NO));
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

static void	options_add_to_string(t_option options, t_buff *dst)
{
	if (option_is_active_in(options, OPT_MONITOR))
		dst->data[dst->len++] = 'm';
	if (option_is_active_in(options, OPT_NOEXEC))
		dst->data[dst->len++] = 'n';
	if (option_is_active_in(options, OPT_NOUNSET))
		dst->data[dst->len++] = 'u';
	if (option_is_active_in(options, OPT_VERBOSE))
		dst->data[dst->len++] = 'v';
	if (option_is_active_in(options, OPT_XTRACE))
		dst->data[dst->len++] = 'x';
	if (option_is_active_in(options, OPT_CMD_STRING))
		dst->data[dst->len++] = 'c';
	if (option_is_active_in(options, OPT_STDIN_INPUT))
		dst->data[dst->len++] = 's';
}

t_error	options_get(t_option options, t_buff *dst)
{
	if (!buff_init(dst, OPT_SINGLE_COUNT + 1, NULL, -1))
		return (error_sys());
	if (option_is_active_in(options, OPT_EXPORT_ALL))
		dst->data[dst->len++] = 'a';
	if (option_is_active_in(options, OPT_NOTIFY))
		dst->data[dst->len++] = 'b';
	if (option_is_active_in(options, OPT_NOCLOBBER))
		dst->data[dst->len++] = 'C';
	if (option_is_active_in(options, OPT_ERREXIT))
		dst->data[dst->len++] = 'e';
	if (option_is_active_in(options, OPT_NOGLOB))
		dst->data[dst->len++] = 'f';
	if (option_is_active_in(options, OPT_HASHALL))
		dst->data[dst->len++] = 'h';
	if (option_is_active_in(options, OPT_INTERACTIVE))
		dst->data[dst->len++] = 'i';
	options_add_to_string(options, dst);
	return (error(ERR_NO));
}
