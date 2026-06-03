/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:32:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 15:09:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TOKEN_H
# define _TOKEN_H

# include "_lexer.h"

void	token_init(t_token *token);
void	token_free(t_token *token);
t_error	token_reset(t_token *res, size_t len);

bool	lexer_quoting(t_lexer *state);								// Rule 4
bool	lexer_comment(t_lexer *state);								// Rule 9
void	lexer_new_word(t_lexer *state);								// Rule 10
bool	lexer_substitution(t_lexer *state);							// Rule 5
bool	lexer_in_middle_of_word(t_lexer *state);					// Rule 8
bool	lexer_blank(t_token *res, t_lexer *state);					// Rule 7
bool	lexer_input_end(t_token *res, t_lexer *state);				// Rule 1
bool	lexer_new_operator(t_token *res, t_lexer *state);			// Rule 6
bool	lexer_in_middle_of_operator(t_token *res, t_lexer *state);	// Rule 2-3

t_error	token_dup(t_token *res, t_token *src);

#endif
