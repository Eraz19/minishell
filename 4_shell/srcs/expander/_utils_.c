/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:54:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 15:45:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "expander_.h"
#include "heredoc.h"

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
