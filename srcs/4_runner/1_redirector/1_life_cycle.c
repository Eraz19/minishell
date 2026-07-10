#include "redirector.h"
#include "redirector_priv.h"
#include "fd_tracker.h"
#include "redirect_stack.h"
#include "fd_manager.h"

void	redirect_init(t_redirector *redirector)
{
	redirector->max_frame_count = 0;
	redirect_stack_init(&redirector->stack);
	fd_tracker_init(&redirector->tracker, &redirector->stack);
}

void	redirect_free(t_redirector *redirector)
{
	(void)fd_restore_stack(redirector);
	redirect_stack_free(&redirector->stack, redirector->max_frame_count);
	fd_tracker_free(&redirector->tracker);
	redirector->max_frame_count = 0;
}

void	redir_init(t_redir *redir, const t_ast_redirection *src)
{
	redir->operation = src->operation;
	redir->expand_heredoc_body = src->expand_heredoc_body;
	redir->fd = src->fd;
	redir->word = &src->word;
	(void)string_init(&redir->expanded_word, 0, NULL, 0);
	redir->is_location = src->is_location;
	redir->location = &src->location;
	(void)string_init(&redir->expanded_location, 0, NULL, 0);
}

void	redir_free(t_redir *redir)
{
	string_free(&redir->expanded_word);
	string_free(&redir->expanded_location);
}
