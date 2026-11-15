/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:48:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_exp_flag	expansion_flags_regular(void)
{
	return (EXP_TILDE_NORMAL | EXP_PARAM | EXP_DOLLAR_SQUOTE | EXP_CMD_SUB
		| EXP_ARITH | EXP_FIELD_SPLIT | EXP_PATH_NAME | EXP_QUOTE_REMOVAL);
}

t_exp_flag	expansion_flags_assignment(void)
{
	return (EXP_TILDE_ASSIGNMENT | EXP_PARAM | EXP_DOLLAR_SQUOTE | EXP_CMD_SUB
		| EXP_ARITH | EXP_QUOTE_REMOVAL);
}

t_exp_flag	expansion_flags_case(void)
{
	return (EXP_TILDE_NORMAL | EXP_PARAM | EXP_DOLLAR_SQUOTE | EXP_CMD_SUB
		| EXP_ARITH | EXP_QUOTE_REMOVAL);
}

t_exp_flag	expansion_flags_redirection(void)
{
	return (EXP_TILDE_NORMAL | EXP_PARAM | EXP_DOLLAR_SQUOTE | EXP_CMD_SUB
		| EXP_ARITH | EXP_QUOTE_REMOVAL);
}

t_exp_flag	expansion_flags_heredoc_body(void)
{
	return (EXP_HEREDOC | EXP_PARAM | EXP_CMD_SUB | EXP_ARITH
		| EXP_QUOTE_REMOVAL);
}
