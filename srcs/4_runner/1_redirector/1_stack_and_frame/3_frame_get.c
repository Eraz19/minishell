#include "redirect_stack.h"

t_error	redirect_frame_get_backup(
			const t_redir_frame *frame,
			size_t index,
			t_redir_backup **out_backup)
{
	if (index >= frame->len)
		return (error_print(error(ERR_INTERNAL),
			"redirect frame doesn't contain the required index", NULL, NULL));
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
