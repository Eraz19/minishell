/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 23:14:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 23:47:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expander.h"

void	expander_init(t_expansion *expansion)
{
	vector_init(expansion, sizeof(char *), 0);
}

void	expander_free(t_expansion *expansion)
{
	vector_free(expansion, free);
}

t_error	expander_load(t_expansion *expansion, char *word)
{
	if (!vector_push(expansion, &word))
		return (ERR_LIBC);
	return (ERR_NO);
}
