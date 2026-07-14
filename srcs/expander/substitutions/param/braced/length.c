#include <stdlib.h>
#include "params.h"
#include "param_braced_.h"
#include "param_expansion_.h"

static t_error	braced_length_finish(
					t_expander *expander,
					t_string *value,
					t_word_item_opt opt)
{
	char		*digits;
	t_string	len_str;

	digits = ft_utoa((unsigned int)value->len);
	string_free(value);
	if (digits == NULL)
		return (expander->err = error_sys());
	if (!string_init(&len_str, 0, digits, -1))
		return (free(digits), expander->err = error_sys());
	free(digits);
	return (braced_finish(expander, &len_str, opt));
}

static t_error	braced_count(t_expander *expander, t_word_item_opt opt)
{
	t_string	count;

	if (braced_expect_close(expander).type)
		return (expander->err);
	expander->err = params_get_from_const("#", &count);
	if (expander->err.type)
		return (expander->err);
	if (count.data == NULL && !string_init(&count, 0, "0", -1))
		return (expander->err = error_sys());
	return (braced_finish(expander, &count, opt));
}

static t_error	braced_length_named(
					t_expander *expander,
					size_t body_len,
					t_word_item_opt opt)
{
	t_string	name;
	t_string	value;
	size_t		len_before;

	len_before = expander->word.len;
	expander->err = get_param_name(expander, &name, true);
	if (expander->err.type)
		return (expander->err);
	if (len_before - expander->word.len != body_len - 1
		|| braced_expect_close(expander).type)
		return (string_free(&name),
			expander->err = error(ERR_PARAM_BAD_SUBSTITUTION));
	expander->err = braced_lookup(expander, &name, &value);
	string_free(&name);
	if (expander->err.type)
		return (expander->err);
	return (braced_length_finish(expander, &value, opt));
}

t_error	expand_braced_length(
			t_expander *expander,
			size_t body_len,
			t_word_item_opt opt)
{
	t_word_item	item;

	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '}')
		return (braced_count(expander, opt));
	if ((item.c == '@' || item.c == '*') && body_len == 2)
	{
		expander->err = word_remove(&expander->word, 0, 1);
		if (expander->err.type)
			return (expander->err);
		return (braced_count(expander, opt));
	}
	return (braced_length_named(expander, body_len, opt));
}
