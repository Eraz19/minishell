#include "field_splitting_.h"

bool	is_delim(t_word_item item, const t_string *ifs)
{
	bool	is_ifs_char;
	bool	is_unquoted;
	bool	is_expand_res;

	is_unquoted = !item.opt.quoted;
	is_expand_res = item.opt.is_expand_res;
	is_ifs_char = string_get_index_c(ifs, item.c) >= 0;
	return (is_expand_res && is_ifs_char && is_unquoted);
}

t_error	delim_field(t_expander *expander)
{
	expander->err = fields_push(&expander->fields_exp, expander->word_exp);
	if (expander->err.type)
		return (expander->err);
	return (word_init(&expander->word_exp), expander->err);
}
