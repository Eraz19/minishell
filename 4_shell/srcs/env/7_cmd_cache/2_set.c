/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:59 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_cache.h"
#include "options.h"
#include <stdlib.h>

t_error	cmd_cache_set(
			t_cmd_cache *cache,
			const t_string *cmd_name,
			const t_string *cmd_path)
{
	bool		hash_cmds_is_active;
	t_string	*allocd_string;
	t_error		err;

	err = option_is_active(OPT_CMD_HASH, &hash_cmds_is_active);
	if (err.type)
		return (err);
	if (hash_cmds_is_active == false)
		return (err);
	allocd_string = malloc(sizeof(*allocd_string));
	if (allocd_string == NULL)
		return (error_sys());
	if (!string_init(allocd_string, cmd_path->len + 1,
			cmd_path->data, (long)cmd_path->len))
		return (err = error_sys(), free(allocd_string), err);
	if (!hashmap_put(cache, cmd_name->data, allocd_string))
	{
		err = error_sys();
		string_free(allocd_string);
		free(allocd_string);
		return (err);
	}
	return (err);
}
