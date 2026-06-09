/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:29:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:16:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "__alias.h"

void	alias_init(t_alias *state)
{
	*state = (t_alias){0};
	alias_stack_init(&state->stack);	
}

void	alias_free(t_alias *state)
{
	alias_stack_free(&state->stack);
	*state = (t_alias){0};
}
