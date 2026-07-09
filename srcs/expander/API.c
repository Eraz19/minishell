#include "error.h"
#include "heredoc.h"
#include "expander.h"
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

t_error expand_str(t_expansion *out, const t_string *src, t_exp_flag flags)
{
	return (expand_heredoc(out, src, flags));
}

t_error	expand_token(t_expansion *out, const t_token *src, t_exp_flag flags)
{
	t_expander_args	args;

	args.flags = flags;
	args.value = src->value;
	args.contexts = &src->contexts;
	args.assignment_offset = src->assignment_offset;
	return (run_expansion(out, &args));
}

t_error	expand_heredoc(t_expansion *out, const t_string *src, t_exp_flag flags)
{
	t_error			err;
	t_string		body;
	t_expander_args	args;
	t_context_stack	contexts;

	if (src->data == NULL || src->len == 0)
		return (expansion_load_empty(out));
	context_stack_init(&contexts);
	if (!string_dup(&body, src))
		return (context_stack_free(&contexts), error_sys());
	err = heredoc_prepare_for_expansion(&contexts, &body);
	if (err.type)
		return (context_stack_free(&contexts), string_free(&body), err);
	args.value = body;
	args.flags = flags;
	args.contexts = &contexts;
	args.assignment_offset = -1;
	err = run_expansion(out, &args);
	return (context_stack_free(&contexts), string_free(&body), err);
}
