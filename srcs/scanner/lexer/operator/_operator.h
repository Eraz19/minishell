/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _operator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:59:32 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 16:53:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OPERATOR_H
# define _OPERATOR_H

# include <stdbool.h>
# include "../_lexer.h"
# include "../token/_token.h"

typedef struct s_operator_args
{
	size_t			len;
	t_token_type	type;
	int				value;
}	t_operator_args;

bool	is_operator(t_lexer *lexer, t_operator_args *args, size_t i);

bool	is_less(t_lexer *lexer, t_operator_args *args, size_t i);
bool	is_great(t_lexer *lexer, t_operator_args *args, size_t i);
bool	is_semi(t_lexer *lexer, t_operator_args *args, size_t i);
bool	is_pipe(t_lexer *lexer, t_operator_args *args, size_t i);
bool	is_newline(t_lexer *lexer, t_operator_args *args, size_t i);
bool	is_io_number(t_lexer *lexer, t_operator_args *args, size_t i);
bool	is_ampersand(t_lexer *lexer, t_operator_args *args, size_t i);
bool	is_parenthesis(t_lexer *lexer, t_operator_args *args, size_t i);

#endif
