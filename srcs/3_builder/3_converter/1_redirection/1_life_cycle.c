#include "ast_type.h"
#include <stdlib.h>

void	ast_redirection_init(t_ast_redirection *redirection)
{
	redirection->operation = AST_REDIR_COUNT;
	redirection->fd = -1;
	redirection->is_location = false;
	buff_init(&redirection->location, 0, NULL, -1);
	buff_init(&redirection->word, 0, NULL, -1);
	redirection->expand_heredoc_body = false;
}

void	ast_redirection_free(void *redirection)
{
	t_ast_redirection	*redir;

	redir = (t_ast_redirection *)redirection;
	redir->operation = AST_REDIR_COUNT;
	redir->fd = -1;
	redir->is_location = false;
	buff_free(&redir->location);
	buff_free(&redir->word);
	redir->expand_heredoc_body = false;
}

void	ast_redir_list_init(t_ast_redir_list *redir_list)
{
	vector_init(redir_list, sizeof(t_ast_redirection), 0);
}

void	ast_redir_list_free(t_ast_redir_list *redir_list)
{
	vector_free(redir_list, ast_redirection_free);
}
