#include "libft.h"
#include "error.h"
#include <stddef.h>
#include <stdlib.h>

#define ESCAPED_QUOTE 					"'\\''"
#define ESCAPED_QUOTE_LEN				4
#define ESCAPED_QUOTE_ADDITIONAL_LEN	3

static void copy_with_escape(const char *src, char **dst, size_t dst_cap)
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
		return (ERR_LIBC);
	copy_with_escape(src, dst, dst_cap);
	return (ERR_NO);
}

// @ret ERR_INVALID_FORMAT
static t_error copy_without_escape(const char *src, char **dst, size_t src_len)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	while (i < src_len - 1)
	{
		(*dst)[j] = src[i];
		if (src[i] == '\'')
		{
			if (str_ncmp(src + i, ESCAPED_QUOTE, ESCAPED_QUOTE_LEN) != 0)
			{
				error_print("deserializer", src, ERR_INVALID_FORMAT);
				free(*dst);
				*dst = NULL;
				return (ERR_INVALID_FORMAT);
			}
			i += ESCAPED_QUOTE_ADDITIONAL_LEN;
		}
		i++;
		j++;
	}
	(*dst)[j] = '\0';
	return (ERR_NO);
}

t_error deserialize(const char *src, char **dst)
{
	size_t	src_len;

	src_len = str_len(src);
	if (src_len < 2 || src[0] != '\'' || src[src_len - 1] != '\'')
		return (error_print("deserializer", src, ERR_INVALID_FORMAT));
	*dst = malloc(src_len + 1);
	if (!*dst)
		return (ERR_LIBC);
	return (copy_without_escape(src, dst, src_len));
}
