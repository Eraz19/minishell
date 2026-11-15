/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_frame_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:13 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:11:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_stack.h"

t_error	redirect_frame_get_backup(
			const t_redir_frame *frame,
			size_t index,
			t_redir_backup **out_backup)
{
	if (index >= frame->len)
		return (error_print(error(ERR_INTERNAL),
				"redirect frame doesn't contain the required index",
				NULL, NULL));
	*out_backup = &((t_redir_backup *)frame->data)[index];
	return (error(ERR_NO));
}

t_error	redirect_frame_get_current_backup(
			const t_redir_frame *frame,
			t_redir_backup **out_current_backup)
{
	if (frame->len == 0)
		return (error_print(error(ERR_INTERNAL),
				"redirect frame is empty", NULL, NULL));
	return (redirect_frame_get_backup(
			frame, frame->len - 1, out_current_backup));
}
