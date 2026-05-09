#include "error.h"
#include "options.h"
#include <stdlib.h>

static void	options_add_to_string(char **dst, size_t *i_ptr)
{
	size_t	i;

	i = *i_ptr;
	if (option_is_active(OPT_MONITOR))
		(*dst)[i++] = 'm';
	if (option_is_active(OPT_NOEXEC))
		(*dst)[i++] = 'n';
	if (option_is_active(OPT_NOUNSET))
		(*dst)[i++] = 'u';
	if (option_is_active(OPT_VERBOSE))
		(*dst)[i++] = 'v';
	if (option_is_active(OPT_XTRACE))
		(*dst)[i++] = 'x';
	if (option_is_active(OPT_CMD_STRING))
		(*dst)[i++] = 'c';
	if (option_is_active(OPT_STDIN_INPUT))
		(*dst)[i++] = 's';
	*i_ptr = i;
}

t_error	options_to_string(char **dst)
{
	size_t	i;

	*dst = malloc(OPT_SINGLE_COUNT + 1);
	if (!*dst)
		return (ERR_LIBC);
	i = 0;
	if (option_is_active(OPT_EXPORT_ALL))
		(*dst)[i++] = 'a';
	if (option_is_active(OPT_NOTIFY))
		(*dst)[i++] = 'b';
	if (option_is_active(OPT_NOCLOBBER))
		(*dst)[i++] = 'C';
	if (option_is_active(OPT_ERREXIT))
		(*dst)[i++] = 'e';
	if (option_is_active(OPT_NOGLOB))
		(*dst)[i++] = 'f';
	if (option_is_active(OPT_HASHALL))
		(*dst)[i++] = 'h';
	if (option_is_active(OPT_INTERACTIVE))
		(*dst)[i++] = 'i';
	options_add_to_string(dst, &i);
	(*dst)[i] = '\0';
	return (ERR_NO);
}
