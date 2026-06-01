/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _operator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:06:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:21:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OPERATOR_H
# define _OPERATOR_H

# include "../_lexer.h"

bool	is_in_middle_of_operator(t_lexer *state);

void	operator_add_less(t_lexer *state);
void	operator_add_pipe(t_lexer *state);
void	operator_add_great(t_lexer *state);
void	operator_add_semicolon(t_lexer *state);
void	operator_add_ampersand(t_lexer *state);

bool	is_operator_char_less(t_lexer *state);
bool	is_operator_char_pipe(t_lexer *state);
bool	is_operator_char_great(t_lexer *state);
bool	is_operator_char_semicolon(t_lexer *state);
bool	is_operator_char_ampersand(t_lexer *state);

#endif
