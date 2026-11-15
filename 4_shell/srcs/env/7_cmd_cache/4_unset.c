/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:03 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_cache.h"

void	cmd_cache_unset(t_cmd_cache *cache, const t_string *cmd_name)
{
	(void)hashmap_remove(cache, cmd_name->data);
}
