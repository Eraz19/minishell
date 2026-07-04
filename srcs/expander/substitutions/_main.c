#include "param_expansion_.h"
#include "tilde_expansion_.h"
#include "cmd_substitution_.h"
#include "arith_substitution_.h"
#include "backtick_substitution_.h"
#include "expander_substitutions_.h"
#include "dollar_squote_expansion_.h"

t_error	substitution_char(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (is_tilde_expansion(expander, &item))
		return (tilde_expansion(expander));
	else if (is_dollar_squote_expansion(&item, expander->flags))
			return (dollar_squote_expansion(expander));
	else if (is_param_expansion(expander, &item))
			return (param_expansion(expander));
	else if (is_cmd_substitution(&item, expander->flags))
		return (cmd_substitution(expander));
	else if (is_backtick_substitution(&item, expander->flags))
		return (backtick_substitution(expander));
	else if (is_arith_substitution(&item, expander->flags))
		return (arith_substitution(expander));
	expander->err = word_push(&expander->word_exp, item);
	if (expander->err.type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 0, 1));
}

t_error	substitution_word(t_expander *expander)
{
	expander->err = fields_fpop(&expander->word, &expander->fields);
	if (expander->err.type)
		return (expander->err);
	word_init(&expander->word_exp);
	while (expander->word.len > 0)
	{
		if (substitution_char(expander).type)
			return (expander->err);
	}
	word_free(&expander->word);
	expander->err = fields_push(&expander->fields_exp, expander->word_exp);
	return (expander->err);
}

t_error	substitutions(t_expander *expander)
{
	fields_init(&expander->fields_exp);
	while (expander->fields.len > 0)
	{
		if (substitution_word(expander).type)
			return (fields_free(&expander->fields_exp), expander->err);
	}
	fields_free(&expander->fields);
	expander->fields = expander->fields_exp;
	return (expander->err);
}
