#include "libft.h"
#include "error.h"
#include "serialize_priv.h"
#include <stddef.h>
#include <stdlib.h>

// @ret ERR_FORMAT_INVALID
static inline t_error copy_and_remove_escape(
						const char *src,
						char *buff,
						size_t src_len,
						size_t *dst_len)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	while (i < src_len - 1)
	{
		buff[j] = src[i];
		if (src[i] == '\'')
		{
			if (str_ncmp(src + i, ESCAPED_QUOTE, ESCAPED_QUOTE_LEN) != 0)
				return (error_print(error(ERR_FORMAT_INVALID),
					"deserializer", src,
					NULL, NULL));
			i += ESCAPED_QUOTE_ADDITIONAL_LEN;
		}
		i++;
		j++;
	}
	buff[j] = '\0';
	*dst_len = j;
	return (error(ERR_NO));
}

t_error deserialize(const char *src, t_string *dst)
{
	size_t	src_len;
	size_t	dst_len;
	char	*buff;
	t_error	err;

	src_len = str_len(src);
	if (src_len < 2 || src[0] != '\'' || src[src_len - 1] != '\'')
		return (error(ERR_FORMAT_INVALID));
	buff = malloc(src_len + 1);
	if (!buff)
		return (error_sys());
	err = copy_and_remove_escape(src, buff, src_len, &dst_len);
	if (err.type)
		return (free(buff), err);
	string_take(dst, buff, src_len + 1, dst_len);
	return (error(ERR_NO));
}
