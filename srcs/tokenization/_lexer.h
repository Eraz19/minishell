/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:03:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/22 17:22:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEXER_H
# define _LEXER_H

#include "lexer.h"

typedef enum e_lexer_token_discriminant
{
	DEFAULT_,		// A non-specific token that doesn't fit into other categories
	CONTROL_,		// A token that represents a control operator (e.g., `|`, `&&`, `;`)
	REDIRECTION_,	// A token that represents a redirection operator (e.g., `>`, `<`, `>>`)
}	t_lexer_token_discriminant;

typedef union u_lexer_token_type
{
	t_lexer_token_discriminant	discriminant;	// Indicates which type of token this is
	t_default_token_id			default_;		// Valid if discriminant == DEFAULT
	t_control_token_id			control_;		// Valid if discriminant == CONTROL
	t_redirection_token_id		redirection_;	// Valid if discriminant == REDIRECTION
}	t_lexer_token_type;

typedef struct s_lexer_token
{
	t_lexer_token_type	type;
	t_token_value		value;
}	t_lexer_token;

char	*remove_escapable_newlines(t_lexer *lexer, char *string);

char	*get_raw_token(t_lexer *lexer, char *string);

#endif
