/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __alias.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:37:41 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 15:02:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ALIAS_H
# define __ALIAS_H

# include "__lexer.h"
# include "__lexer_token.h"
# include "__alias_stack.h"

typedef struct s_alias
{
	t_error			err;
	t_alias_stack	stack;
	t_lexer			*lexer;
	bool			disable_position;
}	t_alias;

void	alias_init(t_alias *state);
void	alias_free(t_alias *state);
t_error	alias_load(t_alias *state, t_token *token);

#endif
