#include "expander_.h"
#include "expansion_.h"
#include "quote_removal_.h"
#include "field_splitting_.h"
#include "path_name_expansion_.h"
#include "expander_substitutions_.h"

t_error	expand_word(t_expander *expander)
{
	if (substitutions(expander).type)
		return (expander->err);
	if (flag_is_active((uint)expander->flags, EXP_FIELD_SPLIT))
	{
		if (field_splitting(expander).type)
			return (expander->err);
	}
	if (flag_is_active((uint)expander->flags, EXP_PATH_NAME))
	{
		if (path_name_expansion(expander).type)
			return (expander->err);
	}
	if (flag_is_active((uint)expander->flags, EXP_QUOTE_REMOVAL))
	{
		if (quote_removal(expander).type)
			return (expander->err);
	}
	return (expander->err);
}

t_error	run_expansion(t_expansion *expansion, t_expander_args *args)
{
	t_error		err;
	t_expander	expander;

	expander_init(&expander);
	expansion_init(expansion);
	if (expander_load(&expander, args).type)
		return (err = expander.err, expander_free(&expander), err);
	if (flag_is_active(expander.flags, EXP_DOLLAR_SQUOTE))
	{
		expander.flags = EXP_DOLLAR_SQUOTE;
		if (substitutions(&expander).type)
			return (err = expander.err, expander_free(&expander), err);
	}
	expander.flags = args->flags & (uint)~EXP_DOLLAR_SQUOTE;
	if (expand_word(&expander).type)
		return (err = expander.err, expander_free(&expander), err);
	expander.err = expansion_load(expansion, &expander.fields);
	return (expander_free(&expander), expander.err);
}
