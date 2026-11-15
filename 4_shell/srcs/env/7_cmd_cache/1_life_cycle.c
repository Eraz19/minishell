/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:57 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:11:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_cache.h"
#include <stdlib.h>

static void	cmd_cache_free_value(void *value)
{
	string_free(value);
	free(value);
}

void	cmd_cache_init(t_cmd_cache *cache)
{
	(void)hashmap_init(cache, 0, cmd_cache_free_value);
}

void	cmd_cache_clear(t_cmd_cache *cache)
{
	hashmap_clear(cache);
}

void	cmd_cache_free(t_cmd_cache *cache)
{
	hashmap_free(cache);
}
