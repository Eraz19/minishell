#include "expander.h"
#include "params.h"

#define NO_FIELD		"converts 0 field into empty field"
#define MULTIPLE_FIELDS	"merging fields with first character of IFS"

// @ret ERR_INTERNAL / ERR_LIBC
static inline t_error	expansion_get_ifs_first_char(char *out)
{
	t_string	ifs;
	t_error		err;

	(void)string_init(&ifs, 0, NULL, 0);
	err = params_get_from_const("IFS", &ifs);
	if (err.type == ERR_VAR_NOT_FOUND || ifs.len == 0)
		return (string_free(&ifs), *out = ' ', error(ERR_NO));
	if (err.type)
		return (error_print(err, NULL, NULL));
	*out = ifs.data[0];
	string_free(&ifs);
	return (err);
}

// @ret ERR_LIBC
static inline t_error	expansion_merge_fields(
							t_expansion *src,
							char sep,
							t_string *out)
{
	size_t	i;
	t_error	err;

	(void)string_init(out, 0, NULL, 0);
	i = 0;
	while (i < src->len)
	{
		if (!string_append(out, &((t_string *)src->data)[0]))
		{
			err = error_print(error_sys(), NULL, NULL);
			return (string_free(out), err);
		}
		if (i < src->len - 1 && !string_append_n(out, &sep, 1))
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
	t_error	err;

	if (src->len == 0)
		print_unspecified_behaviour(raw_value, posix_citation, NO_FIELD);
	else if (src->len > 1)
		print_unspecified_behaviour(raw_value, posix_citation, MULTIPLE_FIELDS);
	err = expansion_get_ifs_first_char(&c);
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
	err = expansion_merge_fields(src, c, out);
	expansion_free(src);
	return (err);
}
