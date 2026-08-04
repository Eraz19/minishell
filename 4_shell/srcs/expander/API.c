/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:55:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "heredoc.h"
#include "expander.h"
#include "expander_.h"
#include "expansion_.h"

t_error	expand_str(
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

t_error	expand_str_merged(
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
