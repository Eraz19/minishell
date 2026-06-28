#include "libft.h"
#include "error.h"
#include "utils.h"
#include "serialize_priv.h"
#include <stddef.h>
#include <stdlib.h>

static inline bool	is_entry_start(const char *src, size_t i)
{
	return (src[i] == '\'' && (i == 0 || src[i - 1] == '\n'));
}

static inline bool	find_entry_end(const char *src, size_t start, size_t *end)
{
	size_t	i;

	i = start + 1;
	while (src[i])
	{
		if (src[i] != '\'')
			i++;
		else if (str_ncmp(src + i, ESCAPED_QUOTE, ESCAPED_QUOTE_LEN) == 0)
			i += ESCAPED_QUOTE_LEN;
		else if (src[i + 1] == '\n' || src[i + 1] == '\0')
			return (*end = i, true);
		else
			return (false);
	}
	return (false);
}

static inline bool	find_next_entry(const char *src, size_t *start, size_t *end)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (is_entry_start(src, i))
		{
			if (find_entry_end(src, i, end))
				return (*start = i, true);
			while (src[i] && src[i] != '\n')
				i++;
		}
		else
			i++;
	}
	return (false);
}

static inline t_error	parse_entry(const char *src, size_t len, t_vector *dst)
{
	t_error	err;
	char	*entry;
	t_string	out;

	entry = str_ndup(src, len);
	if (!entry)
		return (error_sys());
	err = deserialize(entry, &out);
	free(entry);
	if (err.type == ERR_FORMAT_INVALID)
		return (error(ERR_NO));
	if (err.type)
		return (err);
	if (!vector_push(dst, &out))
		return (string_free(&out), error_sys());
	return (error(ERR_NO));
}

t_error	deserialize_all(const char *src, t_vector *dst)
{
	size_t		i;
	size_t		start;
	size_t		end;
	t_error		err;

	if (!vector_init(dst, sizeof(t_string), VECTOR_INIT_CAP))
		return (error_sys());
	i = 0;
	while (src[i])
	{
		if (!find_next_entry(src + i, &start, &end))
			break ;
		err = parse_entry(src + i + start, end - start + 1, dst);
		if (err.type)
			return (vector_free(dst, string_free_void), err);
		i += end + 1;
		while (src[i] == '\n')
			i++;
	}
	return (error(ERR_NO));
}
