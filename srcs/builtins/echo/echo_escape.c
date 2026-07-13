#include "echo_.h"

static bool	echo_map_escape(char c, char *mapped)
{
	static const char	*keys = "abfnrtv\\";
	static const char	*values = "\a\b\f\n\r\t\v\\";
	const char			*pos;

	if (c == '\0')
		return (false);
	pos = str_chr(keys, c);
	if (pos == NULL)
		return (false);
	*mapped = values[pos - keys];
	return (true);
}

static bool	echo_append_octal(t_string *out, const char *arg, size_t *i)
{
	unsigned char	value;
	size_t			digits;

	value = 0;
	digits = 0;
	while (digits < 3 && arg[*i] >= '0' && arg[*i] <= '7')
	{
		value = (unsigned char)(value * 8 + (arg[*i] - '0'));
		(*i)++;
		digits++;
	}
	return (string_append_n(out, (const char *)&value, 1));
}

static bool	echo_append_one(
				t_string *out,
				const char *arg,
				size_t *i,
				bool *stop)
{
	char	mapped;

	if (arg[*i] != '\\')
		return (string_append_n(out, &arg[(*i)++], 1));
	if (arg[*i + 1] == 'c')
		return (*stop = true);
	if (arg[*i + 1] == '0')
		return (*i += 2, echo_append_octal(out, arg, i));
	if (echo_map_escape(arg[*i + 1], &mapped))
		return (*i += 2, string_append_n(out, &mapped, 1));
	return (string_append_n(out, &arg[(*i)++], 1));
}

bool	echo_append_arg(
			t_string *out,
			const char *arg,
			bool escapes,
			bool *stop)
{
	size_t	i;

	if (!escapes)
		return (string_append_n(out, arg, -1));
	i = 0;
	while (arg[i] != '\0' && !*stop)
	{
		if (!echo_append_one(out, arg, &i, stop))
			return (false);
	}
	return (true);
}
