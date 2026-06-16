#include "libft.h"
#include "error.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

t_error assignment_split(const char *src, char **dst_name, char **dst_value)
{
	size_t	len;
	bool	has_equal;
	t_error	err;

	*dst_name = NULL;
	*dst_value = NULL;
	len = 0;
	while (src[len] && src[len] != '=')
		len++;
	if (len == 0)
		return (error(ERR_ASSIGNMENT_MISSING_NAME));
	has_equal = src[len] == '=';
	*dst_name = malloc(len + 1);
	if (!*dst_name)
		return (error_sys());
	str_lcpy(*dst_name, src, len + 1);
	if (!has_equal)
		return (error(ERR_NO));
	*dst_value = str_dup(src + len + 1);
	if (!*dst_value)
	{
		err = error_sys();
		return (free(*dst_name), *dst_name = NULL, err);
	}
	return (error(ERR_NO));
}
