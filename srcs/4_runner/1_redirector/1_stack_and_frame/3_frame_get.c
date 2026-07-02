#include "redirect_stack.h"
#include "redirector_priv.h"

t_error	redirect_frame_get_backup(
			t_redir_frame *frame,
			size_t index,
			t_redir_backup **out_backup)
{
	if (index >= frame->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*out_backup = &((t_redir_backup *)frame->data)[index];
	return (error(ERR_NO));
}

t_error	redirect_frame_get_current_backup(
			t_redir_frame *frame,
			t_redir_backup **out_current_backup)
{
	if (frame->len == 0)
		return (error_print(error(ERR_INDEX_OUT_OF_BOUND),
			REDIRECTOR_MODULE_NAME, "frame is empty", NULL, NULL));
	return (redirect_frame_get_backup(
		frame, frame->len - 1, out_current_backup));
}
