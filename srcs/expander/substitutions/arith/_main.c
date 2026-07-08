#include "expansion_.h"
#include "arith_substitution_.h"

bool	is_arith_substitution(t_word_item *current_item, uint flags)
{
	if (!flag_is_active(flags, EXP_ARITH))
		return (false);
	if (current_item->opt.context == CONTEXT_ARITH)
		return (true);
	return (false);
}

t_error	extract_arith_word(t_expander *expander, t_word *word)
{
	size_t		i;
	size_t		len;
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	len = item.opt.context_len;
	i = 0;
	word_init(word);
	while (i < len)
	{
		expander->err = word_fpop(&item, &expander->word);
		if (expander->err.type)
			return (word_free(word), expander->err);
		if (i > 2 && i < len - 2)
		{
			item.opt.quoted = CONTEXT_DQUOTE;
			expander->err = word_push(word, item);
			if (expander->err.type)
				return (word_free(word), expander->err);
		}
		++i;
	}
	return (expander->err);
}

t_error	compute_arith_expression(t_expander *expander, t_expansion *expansion)
{
	(void)expander;
	(void)expansion;
	return (expander->err);
}

t_error	arith_substitution(t_expander *expander)
{
	t_expansion	expansion;
	t_word		arith_word;
	t_expander	arith_expander;

	if (extract_arith_word(expander, &arith_word).type)
		return (expander->err);
	expander_init(&arith_expander);
	fields_push(&arith_expander.fields, arith_word);
	if (expander->err.type)
		return (expander_free(&arith_expander), expander->err);
	arith_expander.word = arith_word;
	arith_expander.ifs = expander->ifs;
	arith_expander.flags = EXP_PARAM | EXP_CMD_SUB | EXP_QUOTE_REMOVAL;
	expander->err = expand_word(&arith_expander);
	if (expander->err.type)
		return (expander_free(&arith_expander), expander->err);
	expansion_init(&expansion);
	expander->err = expansion_load(&expansion, &arith_expander.fields);
	if (!expander->err.type)
		compute_arith_expression(expander, &expansion);
	expander_free(&arith_expander);
	return (expansion_free(&expansion), expander->err);
}
