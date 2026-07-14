#include "error.h"
#include "heredoc.h"
#include "expander.h"
#include "expander_.h"

t_error	prepare_src(
			t_context_stack *contexts,
			t_string *out,
			const t_string *in,
			t_exp_flag flags)
{
	t_error	err;

	context_stack_init(contexts);
	if (!string_dup(out, in))
		return (context_stack_free(contexts), error_sys());
	if (flag_is_active((uint)flags, EXP_HEREDOC))
		err = heredoc_prepare_for_expansion(contexts, out);
	else
		err = prepare_str_for_expansion(contexts, out);
	if (err.type)
		return (context_stack_free(contexts), string_free(out), err);
	return (error(ERR_NO));
}

t_error	run_and_merge_expansion(t_string *out, t_expander_args *args)
{
	t_error		err;
	t_expansion	exp;

	err = run_expansion(&exp, args);
	if (err.type)
		return (err);
	err = join_expansion(out, &exp, &args->ifs);
	return (expansion_free(&exp), err);
}

t_error expand_str(
			t_string *out,
			const t_string *src,
			int *exit_status,
			t_exp_flag flags)
{

	t_error			err;
	t_expander_args	args;
	t_string		src_dup;
	t_context_stack	contexts;

	if (src->data == NULL || src->len == 0)
		return (string_init(out, 0, NULL, 0), error(ERR_NO));
	err = prepare_src(&contexts, &src_dup, src, flags);
	if (err.type)
		return (context_stack_free(&contexts), expander_error_qualify(err));
	err = get_ifs(&args.ifs);
	if (err.type)
	{
		string_free(&src_dup);
		return (context_stack_free(&contexts), expander_error_qualify(err));
	}
	args.flags = flags;
	args.value = src_dup;
	args.contexts = &contexts;
	args.assignment_offset = -1;
	args.exit_status = exit_status;
	err = run_and_merge_expansion(out, &args);
	return (string_free(&src_dup), string_free(&args.ifs),
		context_stack_free(&contexts), expander_error_qualify(err));
}

t_error	expand_token(
			t_expansion *out,
			const t_token *src,
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
	err = run_expansion(out, &args);
	return (string_free(&args.ifs), expander_error_qualify(err));
}

t_error	expand_token_merged(
			t_string *out,
			const t_token *src,
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
	err = run_and_merge_expansion(out, &args);
	return (string_free(&args.ifs), expander_error_qualify(err));
}
