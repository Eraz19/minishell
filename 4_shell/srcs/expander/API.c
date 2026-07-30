#include "error.h"
#include "heredoc.h"
#include "expander.h"
#include "expander_.h"
#include "expansion_.h"

t_error	prepare_src(
			t_expander_args	*args,
			t_context_stack *context_out,
			t_ast_vector *ast_vec,
			t_exp_flag flags)
{
	t_error	err;

	err = get_ifs(&args->ifs);
	if (err.type)
		return (err);
	if (flag_is_active((uint)flags, EXP_HEREDOC))
		err = heredoc_lex_body(context_out, ast_vec, &args->value);
	else
		err = prepare_str_for_expansion(context_out, ast_vec, &args->value);
	if (err.type)
		return (string_free(&args->value), err);
	args->flags = flags;
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
			t_expansion *out,
			const t_string *src,
			int *exit_status,
			t_exp_flag flags)
{
	t_error			err;
	t_expander_args	args;
	t_ast_vector	ast_vec;
	t_context_stack	contexts;

	args = (t_expander_args){0};
	if (src->data == NULL || src->len == 0)
		return (expansion_init(out), error(ERR_NO));
	if (!string_dup(&args.value, src))
		return (error_sys());
	err = prepare_src(&args, &contexts, &ast_vec, flags);
	if (err.type)
		return (string_free(&args.ifs), string_free(&args.value),
			expander_error_qualify(err));
	args.ast_vec = &ast_vec;
	args.contexts = &contexts;
	args.assignment_offset = -1;
	args.exit_status = exit_status;
	err = run_expansion(out, &args);
	return (expander_args_free(&args), expander_error_qualify(err));
}

t_error expand_str_merged(
			t_string *out,
			const t_string *src,
			int *exit_status,
			t_exp_flag flags)
{

	t_error			err;
	t_expander_args	args;
	t_ast_vector	ast_vec;
	t_context_stack	contexts;

	args = (t_expander_args){0};
	if (src->data == NULL || src->len == 0)
		return (string_init(out, 0, NULL, 0), error(ERR_NO));
	if (!string_dup(&args.value, src))
		return (error_sys());
	err = prepare_src(&args, &contexts, &ast_vec, flags);
	if (err.type)
		return (string_free(&args.ifs), string_free(&args.value),
			expander_error_qualify(err));
	args.ast_vec = &ast_vec;
	args.contexts = &contexts;
	args.assignment_offset = -1;
	args.exit_status = exit_status;
	err = run_and_merge_expansion(out, &args);
	return (expander_args_free(&args), expander_error_qualify(err));
}

t_error	expand_token(
			t_expansion *out,
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
	err = run_expansion(out, &args);
	return (string_free(&args.ifs), expander_error_qualify(err));
}

t_error	expand_token_merged(
			t_string *out,
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
	err = run_and_merge_expansion(out, &args);
	return (string_free(&args.ifs), expander_error_qualify(err));
}
