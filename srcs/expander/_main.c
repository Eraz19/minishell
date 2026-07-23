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

static t_error	run_pipeline(t_expander *expander, t_expander_args *args)
{
	expander_init(expander);
	if (expander_load(expander, args).type)
		return (expander->err);
	if (flag_is_active(expander->flags, EXP_DOLLAR_SQUOTE))
	{
		expander->flags = EXP_DOLLAR_SQUOTE;
		if (substitutions(expander).type)
			return (expander->err);
	}
	expander->flags = args->flags & (uint)~EXP_DOLLAR_SQUOTE;
	return (expand_word(expander));
}

t_error	run_expansion(t_expansion *expansion, t_expander_args *args)
{
	t_error		err;
	t_expander	expander;

	expansion_init(expansion);
	if (run_pipeline(&expander, args).type)
		return (err = expander.err, expander_free(&expander), err);
	expander.err = expansion_load(expansion, &expander.fields);
	return (expander_free(&expander), expander.err);
}

t_error	run_expansion_word(t_fields *out, t_expander_args *args)
{
	t_error		err;
	t_expander	expander;

	fields_init(out);
	if (run_pipeline(&expander, args).type)
		return (err = expander.err, expander_free(&expander), err);
	out->item_size = expander.fields.item_size;
	out->data = expander.fields.data;
	out->cap = expander.fields.cap;
	out->len = expander.fields.len;
	expander.fields.cap = 0;
	expander.fields.data = NULL;
	expander.fields.len = 0;
	return (expander_free(&expander), expander.err);
}

t_error	expand_token_word(
			t_fields *out,
			t_token *src,
			int *exit_status,
			t_exp_flag flags)
{
	t_error			err;
	t_expander_args	args;

	err = get_ifs(&args.ifs);
	if (err.type)
		return (expander_error_qualify(err));
	args.flags = flags;
	args.value = src->value;
	args.contexts = &src->contexts;
	args.exit_status = exit_status;
	args.assignment_offset = src->assignment_offset;
	args.ast_vec = &src->ast_vector;
	err = run_expansion_word(out, &args);
	return (string_free(&args.ifs), expander_error_qualify(err));
}
