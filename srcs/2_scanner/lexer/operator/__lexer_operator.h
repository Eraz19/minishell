/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __lexer_operator.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:06:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:17:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXER_OPERATOR_H
# define __LEXER_OPERATOR_H

# include "__lexer.h"

bool	is_in_middle_of_operator(t_lexer *state);

bool	is_operator_char_less(t_lexer *state);
bool	is_operator_char_pipe(t_lexer *state);
bool	is_operator_char_great(t_lexer *state);
bool	is_operator_char_semicolon(t_lexer *state);
bool	is_operator_char_ampersand(t_lexer *state);

t_error	operator_add_less(t_lexer *state);
t_error	operator_add_pipe(t_lexer *state);
t_error	operator_add_great(t_lexer *state);
t_error	operator_add_semicolon(t_lexer *state);
t_error	operator_add_ampersand(t_lexer *state);

#endif
