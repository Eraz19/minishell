/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __lexer_rules.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:10:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:19:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXER_RULES_H
# define __LEXER_RULES_H

# include "__lexer.h"

bool	is_end(t_lexer *state);
bool	is_blank(t_lexer *state);
bool	is_comment(t_lexer *state);
bool	is_new_operator(t_lexer *state);
bool	is_in_middle_of_word(t_lexer *state);

void	lexer_rule_comment(t_lexer *state);									// Rule 9
t_error	lexer_rule_new_word(t_lexer *state);								// Rule 10
t_error	lexer_rule_in_middle_of_word(t_lexer *state);						// Rule 8
t_error	lexer_rule_end(t_lexer *state, t_token *token);						// Rule 1
t_error	lexer_rule_blank(t_lexer *state, t_token *token); 					// Rule 7
t_error	lexer_rule_quoting(t_lexer *state, t_context context);				// Rule 4
t_error	lexer_rule_expansion(t_lexer *state, t_context context);			// Rule 5
t_error	lexer_rule_new_operator(t_lexer *state, t_token *token);			// Rule 6
t_error	lexer_rule_in_middle_of_operator(t_lexer *state, t_token *token);	// Rule 2-3

#endif
