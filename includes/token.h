/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:32:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 18:48:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "error.h"
# include "libft.h"

typedef enum e_token_type
{
	NONE,
	TOKEN,
	NEWLINE_,
	SCOLON,
	AMPERSAND,
	DSEMI,
	SEMI_AND,
	AND_IF,
	OR_IF,
	PIPE,
	LPARENTHESIS,
	RPARENTHESIS,
	LESSAND,
	GREATAND,
	LESS,
	GREAT,
	CLOBBER,
	LESSGREAT,
	DGREAT,
	DLESS,
	DLESSDASH,
	EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	t_buff			value;
}	t_token;

void	token_init(t_token *token);
void	token_free(t_token *token);
t_error	token_reset(t_token *token, size_t len);

t_error	token_dup(t_token *dst, t_token *src);

#endif
