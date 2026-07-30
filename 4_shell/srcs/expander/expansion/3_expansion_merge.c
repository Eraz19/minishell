#include "expander.h"
#include "env.h"

#define NO_FIELD		"converts 0 field into empty field"
#define MULTIPLE_FIELDS	"merging fields with first IFS character"

/*
- If IFS contains at least one character => use first IFS character
- If IFS is unset => use ' '
- If IFS is set but null => don't use separator
*/

// @ret ERR_INTERNAL / ERR_LIBC
static inline t_error	expansion_get_ifs_first_char(char *out, bool *sep)
{
	t_string	ifs;
	t_error		err;

	(void)string_init(&ifs, 0, NULL, 0);
	err = env_get_from_const("IFS", &ifs);
	if (err.type == ERR_VAR_NOT_FOUND)
	{
		*out = ' ';
		*sep = true;
		string_free(&ifs);
		return (error(ERR_NO));
	}
	else if (err.type)
		return (error_print(err, NULL, NULL));
	else if (ifs.len == 0)
	{
		*sep = false;
		string_free(&ifs);
		return (error(ERR_NO));
	}
	*out = ifs.data[0];
	*sep = true;
	string_free(&ifs);
	return (err);
}

// @ret ERR_LIBC
static inline t_error	expansion_merge_fields(
							t_expansion *src,
							char c,
							bool sep,
							t_string *out)
{
	size_t	i;
	t_error	err;

	(void)string_init(out, 0, NULL, 0);
	i = 0;
	while (i < src->len)
	{
		if (!string_append(out, &((t_string *)src->data)[i]))
		{
			err = error_print(error_sys(), NULL, NULL);
			return (string_free(out), err);
		}
		if (sep == true && i < src->len - 1 && !string_append_n(out, &c, 1))
		{
			err = error_print(error_sys(), NULL, NULL);
			return (string_free(out), err);
		}
		i++;
	}
	return (error(ERR_NO));
}

t_error	expansion_merge(
			const char *raw_value,
			const char *posix_citation,
			t_expansion *src,
			t_string *out)
{
	char	c;
	bool	sep;
	t_error	err;

	if (src->len == 0)
		print_unspecified_behaviour(raw_value, posix_citation, NO_FIELD);
	else if (src->len > 1)
		print_unspecified_behaviour(raw_value, posix_citation, MULTIPLE_FIELDS);
	err = expansion_get_ifs_first_char(&c, &sep);
	if (err.type)
		return (expansion_free(src), err);
	if (src->len == 0)
	{
		if (!string_init(out, 1, "", 0))
		{
			err = error_print(error_sys(), NULL, NULL);
			expansion_free(src);
			return (err);
		}
		expansion_free(src);
		return (err);
	}
	err = expansion_merge_fields(src, c, sep, out);
	expansion_free(src);
	return (err);
}
