/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:18:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:39:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "error.h"
# include "token.h"

typedef t_vector	t_alias_stack;

typedef struct s_alias
{
	t_error			err;
	t_hashmap		map;
	t_alias_stack	stack;
	bool			disable_position;
}	t_alias;

void	alias_init(t_alias *state);
void	alias_free(t_alias *state);

t_error	alias_on_expansion_end(void);
t_error	alias_print(const char *name);
t_error	alias_remove(const char *name);
t_error	alias_add(const char *name, const char *value);
t_error	alias_expand_token(char **expansion, t_buff *token_value);

#endif
