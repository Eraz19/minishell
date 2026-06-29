#include "libft.h"
#include "error.h"
#include "serialize_priv.h"
#include <stddef.h>
#include <stdlib.h>

static inline void copy_and_add_escape(
					const char *src,
					char *buff,
					size_t buff_cap,
					t_string *dst)
{
	size_t	i;
	size_t	j;

	buff[0] = '\'';
	i = 0;
	j = 1;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			str_lcpy(buff + j, ESCAPED_QUOTE, dst->cap - j);
			j += ESCAPED_QUOTE_ADDITIONAL_LEN;
		}
		else
			buff[j] = src[i];
		i++;
		j++;
	}
	buff[j] = '\'';
	buff[j + 1] = '\0';
	string_take(dst, buff, buff_cap, j + 1);
}

t_error serialize(const char *src, t_string *dst)
{
	size_t	src_len;
	size_t	buff_cap;
	size_t	escape_count;
	char	*buff;

	escape_count = 0;
	src_len = 0;
	while (src[src_len])
		if (src[src_len++] == '\'')
			escape_count++;
	buff_cap = src_len + 2 + (escape_count * ESCAPED_QUOTE_ADDITIONAL_LEN) + 1;
	buff = malloc(buff_cap);
	if (!buff)
		return (error_sys());
	copy_and_add_escape(src, buff, buff_cap, dst);
	return (error(ERR_NO));
}
