#include "libft.h"
#include "error.h"
#include "serialize_priv.h"
#include <stddef.h>
#include <stdlib.h>

static inline void copy_and_add_escape(
	const char *src,
	char **dst,
	size_t dst_cap)
{
	size_t	i;
	size_t	j;

	(*dst)[0] = '\'';
	i = 0;
	j = 1;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			str_lcpy(*dst + j, ESCAPED_QUOTE, dst_cap - j);
			j += ESCAPED_QUOTE_ADDITIONAL_LEN;
		}
		else
			(*dst)[j] = src[i];
		i++;
		j++;
	}
	(*dst)[dst_cap - 2] = '\'';
	(*dst)[dst_cap - 1] = '\0';
}

t_error serialize(const char *src, char **dst)
{
	size_t	src_len;
	size_t	dst_cap;
	size_t	escape_count;

	escape_count = 0;
	src_len = 0;
	while (src[src_len])
		if (src[src_len++] == '\'')
			escape_count++;
	dst_cap = src_len + 2 + (escape_count * ESCAPED_QUOTE_ADDITIONAL_LEN) + 1;
	*dst = malloc(dst_cap);
	if (!*dst)
		return (error_sys());
	copy_and_add_escape(src, dst, dst_cap);
	return (error(ERR_NO));
}
