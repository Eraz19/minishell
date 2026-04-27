/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:03:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 15:08:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEXER_H
# define _LEXER_H

#include "lexer.h"

typedef enum e_lexer_token_type
{
	DEFAULT_,		// A non-specific token that doesn't fit into other categories
	CONTROL_,		// A token that represents a control operator (e.g., `|`, `&&`, `;`)
	REDIRECTION_,	// A token that represents a redirection operator (e.g., `>`, `<`, `>>`)
}	t_lexer_token_type;
	
typedef union u_lexer_token_id
{
	t_default_token_id			default_;		// Valid if discriminant == DEFAULT
	t_control_token_id			control_;		// Valid if discriminant == CONTROL
	t_redirection_token_id		redirection_;	// Valid if discriminant == REDIRECTION
}	t_lexer_token_id;

typedef struct s_lexer_token
{
	t_lexer_token_type	type;
	t_lexer_token_id	id;
	t_token_value		value;
	size_t				offset;
}	t_lexer_token;

t_lexer_token	*eof(size_t offset);
t_lexer_token	*newline(size_t offset);
t_lexer_token	*semicolon(size_t offset);
t_lexer_token	*ampersand(size_t offset);
t_lexer_token	*dsemi(size_t offset);
t_lexer_token	*semi_and(size_t offset);
t_lexer_token	*or_if(size_t offset);
t_lexer_token	*and_if(size_t offset);
t_lexer_token	*pipe(size_t offset);
t_lexer_token	*lparenthesis(size_t offset);
t_lexer_token	*rparenthesis(size_t offset);

bool			is_dsemi(t_raw_string input_ptr);
bool			is_semi_and(t_raw_string input_ptr);
bool			is_newline(t_raw_string input_ptr);
bool			is_semicolon(t_raw_string input_ptr);
bool			is_ampersand(t_raw_string input_ptr);
bool			is_and_if(t_raw_string input_ptr);
bool			is_or_if(t_raw_string input_ptr);
bool			is_pipe(t_raw_string input_ptr);
bool			is_lparenthesis(t_raw_string input_ptr);
bool			is_rparenthesis(t_raw_string input_ptr);

t_lexer_token	*lessand(size_t offset);
t_lexer_token	*greatand(size_t offset);
t_lexer_token	*io_number(size_t offset);
t_lexer_token	*dless(size_t offset);
t_lexer_token	*dlessdash(size_t offset);
t_lexer_token	*less(size_t offset);
t_lexer_token	*great(size_t offset);
t_lexer_token	*dgreat(size_t offset);
t_lexer_token	*clobber(size_t offset);
t_lexer_token	*lessgreat(size_t offset);

bool			is_greatand(t_raw_string input_ptr);
bool			is_lessand(t_raw_string input_ptr);
bool			is_io_number(t_raw_string input_ptr);
bool			is_dless(t_raw_string input_ptr);
bool			is_dlessdash(t_raw_string input_ptr);
bool			is_less(t_raw_string input_ptr);
bool			is_great(t_raw_string input_ptr);
bool			is_clobber(t_raw_string input_ptr);
bool			is_lessgreat(t_raw_string input_ptr);
bool			is_dgreat(t_raw_string input_ptr);

t_raw_string	remove_escapable_newlines(t_raw_string input);

#endif
