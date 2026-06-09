/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:24:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:19:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_rules.h"
#include "__lexer_operator.h"

t_error	lexer_rules(t_lexer *state, t_token *token, t_context *context)
{
	if (is_end(state))
		return (lexer_rule_end(state, token));
	else if (is_in_middle_of_operator(state))
		return (lexer_rule_in_middle_of_operator(state, token));
	else if (is_quoting_context(state->input + state->i, context))
		return (lexer_rule_quoting(state, *context));
	else if (is_expansion_context(state->input + state->i, context))
		return (lexer_rule_expansion(state, *context));
	else if (is_new_operator(state))
		return (lexer_rule_new_operator(state, token));
	else if (is_blank(state))
		return (lexer_rule_blank(state, token));
	else if (is_in_middle_of_word(state))
		return (lexer_rule_in_middle_of_word(state));
	else if (is_comment(state))
		return (lexer_rule_comment(state), state->err);
	else
		return (lexer_rule_new_word(state));
}
