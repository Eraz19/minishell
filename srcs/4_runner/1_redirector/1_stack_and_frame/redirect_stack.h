#ifndef REDIRECT_STACK_H
# define REDIRECT_STACK_H

# include "error.h"
# include "redirect_stack_type.h"

/* ************************************************************************* */
/*                                   STACK                                   */
/* ************************************************************************* */

void	redirect_stack_init(t_redir_stack *stack);
void	redirect_stack_free(t_redir_stack *stack, size_t item_count_to_free);

// @ret ERR_LIBC
t_error	redirect_stack_push(t_redir_stack *stack, t_redir_frame *frame);

// @ret ERR_INDEX_OUT_OF_BOUND
t_error	redirect_stack_get_frame(
			t_redir_stack *stack,
			size_t index,
			t_redir_frame **out_frame);

// @ret ERR_INDEX_OUT_OF_BOUND
t_error	redirect_stack_get_current_frame(
			t_redir_stack *stack,
			t_redir_frame **out_current_frame);

// @ret ERR_INDEX_OUT_OF_BOUND
t_error	redirect_stack_get_backup(
			t_redir_stack *stack,
			size_t frame_index,
			size_t backup_index,
			t_redir_backup **out_backup);

// @ret ERR_INDEX_OUT_OF_BOUND
t_error	redirect_stack_get_current_backup(
			t_redir_stack *stack,
			t_redir_backup **out_current_backup);

/* ************************************************************************* */
/*                                   FRAME                                   */
/* ************************************************************************* */

void	redirect_frame_init(t_redir_frame *frame);
void	redirect_frame_free(t_redir_frame *frame);

// @ret ERR_LIBC
t_error	redirect_frame_push(t_redir_stack *stack, t_redir_backup *backup);

// @ret ERR_INDEX_OUT_OF_BOUND
t_error	redirect_frame_get_backup(
			t_redir_frame *frame,
			size_t index,
			t_redir_backup **out_backup);

// @ret ERR_INDEX_OUT_OF_BOUND
t_error	redirect_frame_get_current_backup(
			t_redir_frame *frame,
			t_redir_backup **out_current_backup);

#endif
