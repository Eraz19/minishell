#include "params.h"
#include "expander_.h"

bool    flag_is_active(uint bitset, uint flag)
{
    return ((bitset & flag) != 0);
}

t_error	forward_word_item(t_word *word_exp, t_word *word)
{
	t_error		err;
	t_word_item	item;

	err = word_fpop(&item, word);
	if (err.type)
		return (err);
	err = word_push(word_exp, item);
	if (err.type)
		return (err);
	return (error(ERR_NO));
}

t_error	get_ifs(t_expander *expander, t_string	*ifs)
{
	string_init(ifs, 0, NULL, 0);
	expander->err = params_get_from_const("IFS", ifs);
	if (expander->err.type != ERR_NO && expander->err.type != ERR_VAR_NOT_FOUND)
		return (string_free(ifs), expander->err);
	if (expander->err.type == ERR_VAR_NOT_FOUND)
	{
		expander->err = error(ERR_NO);
		if (!string_append_n(ifs, " \t\n", 3))
		{
			expander->err = error_sys();
			return (string_free(ifs), expander->err);
		}
	}
	else if (ifs->data == NULL)
	{
		if (!string_append_n(ifs, "", -1))
		{
			expander->err = error_sys();
			return (string_free(ifs), expander->err);
		}
	}
	return (expander->err);
}
