/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_is_same_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:48:09 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:48:10 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

bool	assignment_is_same_name(const char *target, const char *entry)
{
	size_t	i;

	i = 0;
	while (target[i] == entry[i] && target[i] != '=')
		i++;
	return (target[i] == entry[i]);
}
