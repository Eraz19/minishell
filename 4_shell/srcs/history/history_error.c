/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 18:12:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_priv.h"

/*
** History error surface — everything that can bubble up to the API
** endpoints (history_load, history_save, history_save_entry,
** history_append_to_entry):
**
**	- ERR_NO	success, plus every absorbed lane: HISTFILE and HOME both
**				unusable (ERR_HISTORY_DISABLED printed, load continues),
**				history file open/read/write/close failure (diagnostic
**				printed, lane absorbed, persistent history disabled),
**				unset/empty/invalid HISTSIZE, malformed file entries
**				(ERR_FORMAT_INVALID absorbed by deserialize_all's
**				parse_entry, line skipped).
**	- ERR_LIBC	allocation failures only:
**				* history_load <- load_history_path_from_env:
**				  "/.sh_history" append (file_path.c) or env string_dup
**				  (env module)
**				* history_load <- load_history_max_size_env: env
**				  string_dup (env module)
**				* history_load <- history_file_load: deserialize_all
**				  allocations (serializer), entry push (history_list.c)
**				* history_save <- build_saving_file_content: serialize
**				  allocation (serializer), content append
**				  (saving_file_content.c)
**				* history_save_entry <- history_list_push
**				* history_append_to_entry <- string_append
**
** Both types belong to the allowed pass-through set, so this mapping is
** the identity — final, not a placeholder.
**
** CONSTRAINT: shell_load aborts startup on any history_load error —
** every "history disabled" lane must keep leaving this boundary as
** ERR_NO.
*/
t_error	requalify_history_error(t_error err)
{
	return (err);
}
