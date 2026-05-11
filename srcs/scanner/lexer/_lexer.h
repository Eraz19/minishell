/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:31:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 16:58:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEXER_H
# define _LEXER_H

# include <stddef.h>
# include <stdbool.h>

// Forward declarations
typedef struct s_token	t_token;

typedef enum e_lexer_ctx
{
	NONE,
	SQUOTE,    // '
	DQUOTE,    // "
	BACKTICK,  // `
	CMD_SUB,   // $(
	ARITH,     // $((
	PARAM,     // ${
}   t_lexer_ctx_type;

typedef struct s_lexer_ctx
{
	t_lexer_ctx_type	type;
	int					nesting_depth;
}	t_lexer_ctx;

typedef struct s_ctx_stack
{
	size_t		len;
	size_t		size;
	t_lexer_ctx	*data;
}	t_ctx_stack;

typedef struct s_lexer
{
	size_t		i;
	t_ctx_stack	ctx;
	char		*input;
	char		*script_path;
}	t_lexer;

bool	lex_line(t_token **res, t_lexer *lexer);

#endif
