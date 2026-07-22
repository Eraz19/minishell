#include "redirector_priv.h"

t_error	redir_init(t_redir *redir, const t_ast_redirection *src)
{
	t_error	err;

	redir->operation = src->operation;
	redir->expand_heredoc_body = src->expand_heredoc_body;
	redir->fd = src->fd;
	err = token_dup(&redir->word, &src->word);
	if (err.type)
		return (err);
	redir->heredoc_body = &src->heredoc_body;
	(void)string_init(&redir->expanded_word, 0, NULL, 0);
	redir->is_location = src->is_location;
	(void)string_init(&redir->expanded_location, 0, NULL, 0);
	return (token_dup(&redir->location, &src->location));
}

void	redir_free(t_redir *redir)
{
	token_free(&redir->word);
	token_free(&redir->location);
	string_free(&redir->expanded_word);
	string_free(&redir->expanded_location);
}
