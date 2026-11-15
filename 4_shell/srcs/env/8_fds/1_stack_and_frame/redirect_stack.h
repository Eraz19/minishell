/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stack.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_STACK_H
# define REDIRECT_STACK_H

# include "error.h"
# include "redirect_stack_type.h"
# include "fd_tracker_type.h"

/* ************************************************************************* */
/*                                   STACK                                   */
/* ************************************************************************* */

void	redirect_stack_init(t_redir_stack *stack);
void	redirect_stack_clear(t_redir_stack *stack);
void	redirect_stack_free(t_redir_stack *stack, size_t item_count_to_free);

// @ret ERR_LIBC
t_error	redirect_stack_push(t_redir_stack *stack, t_redir_frame *frame);

// @ret ERR_INTERNAL
t_error	redirect_stack_get_frame(
			const t_redir_stack *stack,
			size_t index,
			t_redir_frame **out_frame);

// @ret ERR_INTERNAL
t_error	redirect_stack_get_current_frame(
			const t_redir_stack *stack,
			t_redir_frame **out_current_frame);

// @ret ERR_INTERNAL
t_error	redirect_stack_get_backup(
			const t_redir_stack *stack,
			size_t frame_index,
			size_t backup_index,
			t_redir_backup **out_backup);

// @ret ERR_INTERNAL
t_error	redirect_stack_get_current_backup(
			const t_redir_stack *stack,
			t_redir_backup **out_current_backup);

// 42 constraint: fcntl() is forbidden, so backup fds cannot be marked
// FD_CLOEXEC. Best-effort cleanup in the child before execve().
// This should be replaced by FD_CLOEXEC when fcntl() is available.
void	redirect_stack_close_backups(
			const t_redir_stack *redir_stack,
			t_fd_tracker *tracker);

/* ************************************************************************* */
/*                                   FRAME                                   */
/* ************************************************************************* */

void	redirect_frame_init(t_redir_frame *frame);
void	redirect_frame_free(t_redir_frame *frame);

// @ret ERR_LIBC
t_error	redirect_frame_push(t_redir_stack *stack, t_redir_backup *backup);

// @ret ERR_INTERNAL
t_error	redirect_frame_get_backup(
			const t_redir_frame *frame,
			size_t index,
			t_redir_backup **out_backup);

// @ret ERR_INTERNAL
t_error	redirect_frame_get_current_backup(
			const t_redir_frame *frame,
			t_redir_backup **out_current_backup);

#endif
