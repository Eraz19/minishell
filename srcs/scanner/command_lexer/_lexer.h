/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:03:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/29 18:04:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEXER_H
# define _LEXER_H

#include "scanner.h"

t_token	*eof(size_t offset);
t_token	*newline(size_t offset);
t_token	*semicolon(size_t offset);
t_token	*ampersand(size_t offset);
t_token	*dsemi(size_t offset);
t_token	*semi_and(size_t offset);
t_token	*or_if(size_t offset);
t_token	*and_if(size_t offset);
t_token	*pipe_(size_t offset);
t_token	*lparenthesis(size_t offset);
t_token	*rparenthesis(size_t offset);

bool	is_dsemi(char *input_ptr);
bool	is_semi_and(char *input_ptr);
bool	is_newline(char *input_ptr);
bool	is_semicolon(char *input_ptr);
bool	is_ampersand(char *input_ptr);
bool	is_and_if(char *input_ptr);
bool	is_or_if(char *input_ptr);
bool	is_pipe(char *input_ptr);
bool	is_lparenthesis(char *input_ptr);
bool	is_rparenthesis(char *input_ptr);

t_token	*lessand(size_t offset);
t_token	*greatand(size_t offset);
t_token	*io_number(size_t offset);
t_token	*dless(size_t offset);
t_token	*dlessdash(size_t offset);
t_token	*less(size_t offset);
t_token	*great(size_t offset);
t_token	*dgreat(size_t offset);
t_token	*clobber(size_t offset);
t_token	*lessgreat(size_t offset);

bool	is_greatand(char *input_ptr);
bool	is_lessand(char *input_ptr);
bool	is_io_number(char *input_ptr);
bool	is_dless(char *input_ptr);
bool	is_dlessdash(char *input_ptr);
bool	is_less(char *input_ptr);
bool	is_great(char *input_ptr);
bool	is_clobber(char *input_ptr);
bool	is_lessgreat(char *input_ptr);
bool	is_dgreat(char *input_ptr);

#endif
