/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 18:07:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:42:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "alias_.h"

void	alias_print_one(t_key_value *pair)
{
	if (pair == NULL)
		return ;
	if (pair->value == NULL)
		ft_printf("%s=''\n", pair->key);
	else
		ft_printf("%s='%s'\n", pair->key, (char *)pair->value);	
}

void	alias_print_all(t_key_value **pairs)
{
	size_t	i;

	if (pairs == NULL)
		return ;
	i = 0;
	while (pairs[i] != NULL)
		alias_print_one(pairs[i++]);
}
