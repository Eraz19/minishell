/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_stack_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:16 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:11:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_stack.h"

t_error	redirect_stack_get_frame(
			const t_redir_stack *stack,
			size_t index,
			t_redir_frame **out_frame)
{
	if (index >= stack->len)
		return (error_print(error(ERR_INTERNAL),
				"redirect stack doesn't contain the required index",
				NULL, NULL));
	*out_frame = &((t_redir_frame *)stack->data)[index];
	return (error(ERR_NO));
}

t_error	redirect_stack_get_current_frame(
			const t_redir_stack *stack,
			t_redir_frame **out_current_frame)
{
	if (stack->len == 0)
		return (error_print(error(ERR_INTERNAL),
				"redirect stack is empty", NULL, NULL));
	return (redirect_stack_get_frame(stack, stack->len - 1, out_current_frame));
}

t_error	redirect_stack_get_current_backup(
			const t_redir_stack *stack,
			t_redir_backup **out_current_backup)
{
	t_redir_frame	*frame;
	t_error			err;

	err = redirect_stack_get_current_frame(stack, &frame);
	if (err.type)
		return (err);
	return (redirect_frame_get_current_backup(frame, out_current_backup));
}

t_error	redirect_stack_get_backup(
			const t_redir_stack *stack,
			size_t frame_index,
			size_t backup_index,
			t_redir_backup **out_backup)
{
	t_redir_frame	*frame;
	t_error			err;

	frame = NULL;
	err = redirect_stack_get_frame(stack, frame_index, &frame);
	if (err.type)
		return (err);
	return (redirect_frame_get_backup(frame, backup_index, out_backup));
}
