/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:31:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 17:17:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEXER_H
# define _LEXER_H

# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>
# include "error.h"

// Forward declarations
typedef struct s_token	t_token;







void	free_lexer(t_lexer *lexer);

void	lex_line(t_lex_line_maybe *res, t_lexer *lexer);

bool	is_blank(t_lexer *lexer, size_t i);
bool	is_comment(t_lexer *lexer, size_t i);

void	advance(t_lexer *lexer, size_t offset);

// For testing purposes
/*
typedef struct s_ctx_stack_snapshot
{
	size_t			len;
	size_t			size;
	t_lexer_ctx		data[10];
}	t_ctx_stack_snapshot;

typedef struct s_lexer_snapshot
{
	ssize_t					i;
	t_ctx_stack_snapshot	ctx;
	const char				*input;
	size_t					start_token_i;
	size_t					total_removed_count;
	size_t					current_removed_count;
}	t_lexer_snapshot;

void	DEBUG_print_lexer_state(t_lexer *lexer);
bool	DEBUG_lexer_equal(t_lexer *lexer1, t_lexer_snapshot *lexer2);
*/
#endif
