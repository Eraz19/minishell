/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 19:12:28 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 19:12:29 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "error.h"
# include "libft.h"
# include "context.h" // IWYU pragma: keep
# include "token_pool.h"
# include "ast_vector_type.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

typedef enum e_token_type
{
	TOKEN_NONE,
	TOKEN_TOKEN,
	TOKEN_DOLPAREN,
	TOKEN_NEWLINE,
	TOKEN_SCOLON,
	TOKEN_AMPERSAND,
	TOKEN_DSEMI,
	TOKEN_SEMI_AND,
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_PIPE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_LESSAND,
	TOKEN_GREATAND,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_CLOBBER,
	TOKEN_LESSGREAT,
	TOKEN_DGREAT,
	TOKEN_DLESS,
	TOKEN_DLESSDASH,
	TOKEN_IO_NUMBER,
	TOKEN_IO_LOCATION,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token_index
{
	ssize_t	end;
	ssize_t	start;
	ssize_t	error;
}	t_token_index;

typedef struct s_token
{
	t_token_type	type;
	t_string		value;
	t_token_index	index;
	t_context_stack	contexts;
	t_ast_vector	ast_vector;
	ssize_t			assignment_offset;
}	t_token;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	token_init(t_token *token);

void	token_free(t_token *token);
void	token_free_void(void *token);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	token_dup_void(void *dst, const void *src);

void	token_transfer(t_token *dst, t_token *src);

t_error	token_dup(t_token *dst, const t_token *src);

#endif
