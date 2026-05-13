/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:31:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/13 15:30:22 by adouieb          ###   ########.fr       */
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
	ESCAPED,   // '\'
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
	size_t		total_removed_count; // to track the count of characters removed from the input for accurate token offsets
	size_t		current_removed_count; // to track the count of characters removed in the current tokenization step for accurate token offsets
}	t_lexer;

void	free_lexer(t_lexer *lexer);

bool	lex_line(t_token **res, t_lexer *lexer);

bool	is_blank(t_lexer *lexer, size_t i);
bool	is_comment(t_lexer *lexer, size_t i);

// For testing purposes

typedef struct s_ctx_stack_snapshot
{
	size_t			len;
	size_t			size;
	t_lexer_ctx		data[10];
}	t_ctx_stack_snapshot;

typedef struct s_lexer_snapshot
{
	size_t					i;
	t_ctx_stack_snapshot	ctx;
	const char				*input;
	size_t					total_removed_count;
	size_t					current_removed_count;
}	t_lexer_snapshot;

void	DEBUG_print_lexer_state(t_lexer *lexer);
bool	DEBUG_lexer_equal(t_lexer *lexer1, t_lexer_snapshot *lexer2);

#endif
