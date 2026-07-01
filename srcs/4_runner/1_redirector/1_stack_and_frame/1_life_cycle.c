#include "redirect_priv.h"

void	redirect_frame_init(t_redir_frame *frame)
{
	vector_init(frame, sizeof(t_redir_backup), 0);
}

void	redirect_frame_free(void *frame)
{
	vector_free(frame, NULL);
}
