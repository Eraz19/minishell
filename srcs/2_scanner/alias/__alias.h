/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __alias.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:37:41 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:16:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ALIAS_H
# define __ALIAS_H

# include "__alias_stack.h"

typedef struct s_alias
{
	t_error			err;
	t_alias_stack	stack;
	bool			disable_position;
}	t_alias;

void	alias_init(t_alias *state);
void	alias_free(t_alias *state);

#endif
