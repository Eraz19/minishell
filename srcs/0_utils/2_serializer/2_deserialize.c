#include "libft.h"
#include "error.h"
#include "serialize_priv.h"
#include <stddef.h>
#include <stdlib.h>

// @ret ERR_FORMAT_INVALID
static inline t_error copy_and_remove_escape(
	const char *src,
	char **dst,
	size_t src_len)
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
				free(*dst);
				*dst = NULL;
				return (error_print(error(ERR_FORMAT_INVALID),
					"deserializer", src,
					NULL, NULL));
			}
			i += ESCAPED_QUOTE_ADDITIONAL_LEN;
		}
		i++;
		j++;
	}
	(*dst)[j] = '\0';
	return (error(ERR_NO));
}

t_error deserialize(const char *src, char **dst)
{
	size_t	src_len;

	src_len = str_len(src);
	if (src_len < 2 || src[0] != '\'' || src[src_len - 1] != '\'')
		return (error(ERR_FORMAT_INVALID));
	*dst = malloc(src_len + 1);
	if (!*dst)
		return (error_sys());
	return (copy_and_remove_escape(src, dst, src_len));
}
