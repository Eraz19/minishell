#include "quote_removal_.h"
#include "quote_removal_context_.h"

t_error	quote_removal_quoted(t_expander *expander, t_word_item item)
{
	if (item.opt.quoted == CONTEXT_SQUOTE)
		context_squote(expander);
	else if (item.opt.quoted == CONTEXT_DQUOTE)
		context_dquote(expander);
	else if (item.opt.quoted == CONTEXT_HEREDOC)
		context_heredoc(expander, item);
	else if (item.opt.quoted == CONTEXT_DOLLAR_SQUOTE)
	{
		expander->err = word_fpop(&item, &expander->word);
		if (expander->err.type)
			return (expander->err);
		context_dollar_squote(expander);
	}
	return (expander->err);
}

t_error	quote_remove_char(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_fpop(&item, &expander->word);
	if (expander->err.type)
		return (expander->err);
	if (item.opt.is_expand_res)
		expander->err = word_push(&expander->word_exp, item);
	else if (item.opt.quoted == CONTEXT_NONE)
	{
		if (item.c != '\\')
			expander->err = word_push(&expander->word_exp, item);
		else
		{
			if (expander->word.len == 0)
				return (expander->err = error(ERR_NO));
			expander->err = word_fpop(&item, &expander->word);
			if (expander->err.type)
				return (expander->err);
			expander->err = word_push(&expander->word_exp, item);
		}
	}
	else
		quote_removal_quoted(expander, item);
	return (expander->err);
}

t_error	quote_removal_word(t_expander *expander)
{
	expander->err = fields_fpop(&expander->word, &expander->fields);
	if (expander->err.type)
		return (expander->err);
	word_init(&expander->word_exp);
	while (expander->word.len > 0)
	{
		if (quote_remove_char(expander).type)
			return (expander->err);
	}
	word_free(&expander->word);
	expander->err = fields_push(&expander->fields_exp, expander->word_exp);
	return (expander->err);
}

t_error	quote_removal(t_expander *expander)
{
	fields_init(&expander->fields_exp);
	while (expander->fields.len > 0)
	{
		if (quote_removal_word(expander).type)
			return (fields_free(&expander->fields_exp), expander->err);
	}
	fields_free(&expander->fields);
	expander->fields = expander->fields_exp;
	return (expander->err);
}
