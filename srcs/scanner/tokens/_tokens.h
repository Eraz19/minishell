/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tokens.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:03:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/05 16:08:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TOKENS_H
# define _TOKENS_H

#include "scanner.h"

t_token	*token_(char *input_ptr, size_t len);

t_token	*eof(char *input_ptr);
t_token	*newline(char *input_ptr);
t_token	*semicolon(char *input_ptr);
t_token	*ampersand(char *input_ptr);
t_token	*dsemi(char *input_ptr);
t_token	*semi_and(char *input_ptr);
t_token	*or_if(char *input_ptr);
t_token	*and_if(char *input_ptr);
t_token	*pipe_(char *input_ptr);
t_token	*lparenthesis(char *input_ptr);
t_token	*rparenthesis(char *input_ptr);

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

t_token	*lessand(char *input_ptr);
t_token	*greatand(char *input_ptr);
t_token	*io_number(char *input_ptr);
t_token	*dless(char *input_ptr);
t_token	*dlessdash(char *input_ptr);
t_token	*less(char *input_ptr);
t_token	*great(char *input_ptr);
t_token	*dgreat(char *input_ptr);
t_token	*clobber(char *input_ptr);
t_token	*lessgreat(char *input_ptr);

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
