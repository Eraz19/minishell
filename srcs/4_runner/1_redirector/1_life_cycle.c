#include "redirector.h"
#include "redirector_priv.h"
#include "fd_tracker.h"
#include "redirect_stack.h"
#include "fd_manager.h"

void	redirect_init(t_redirector *redirector)
{
	redirect_stack_init(&redirector->stack);
	fd_tracker_init(&redirector->tracker, &redirector->stack);
	redirector->max_frame_count = 0;
	redirector->heredoc_id = 0;
}

void	redirect_init_subshell(t_redirector *redirector)
{
	(void)redirect_clear(redirector, false);
}

t_error	redirect_clear(t_redirector *redirector, bool restore_redirections)
{
	if (restore_redirections == true)
		return (fd_restore_stack(redirector));
	redirect_stack_close_backups(&redirector->stack, &redirector->tracker);
	redirect_stack_clear(&redirector->stack);
	return (error(ERR_NO));
}

void	redirect_free(t_redirector *redirector)
{
	(void)fd_restore_stack(redirector);
	redirect_stack_free(&redirector->stack, redirector->max_frame_count);
	fd_tracker_free(&redirector->tracker);
	redirector->max_frame_count = 0;
	redirector->heredoc_id = 0;
}

void	redir_init(t_redir *redir, const t_ast_redirection *src)
{
	redir->operation = src->operation;
	redir->expand_heredoc_body = src->expand_heredoc_body;
	redir->fd = src->fd;
	redir->word = &src->word;
	redir->heredoc_body = &src->heredoc_body;
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
