/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:29:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 17:51:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "alias.h"
#include "alias_stack_.h"

void	alias_init(t_alias *state)
{
	*state = (t_alias){0};
	alias_stack_init(&state->stack);
	hashmap_init(&state->map, 0, free);
}

void	alias_free(t_alias *state)
{
	alias_stack_free(&state->stack);
	hashmap_free(&state->map);
	*state = (t_alias){0};
}
