#include "ast.h"
# include <assert.h>	// DEBUG

void	ast_redirection_init(t_ast_redirection *redirection)
{
	assert(redirection != NULL);
	redirection->operation = AST_REDIR_COUNT;
	redirection->expand_heredoc_body = false;
	redirection->fd = -1;
	token_init(&redirection->word);
	(void)string_init(&redirection->heredoc_body, 0, NULL, 0);
	redirection->is_location = false;
	token_init(&redirection->location);
}

void	ast_redirection_free(void *redirection)
{
	t_ast_redirection	*redir;

	assert(redirection != NULL);
	redir = (t_ast_redirection *)redirection;
	token_free(&redir->word);
	string_free(&redir->heredoc_body);
	token_free(&redir->location);
	ast_redirection_init(redir);
}

void	ast_redir_list_init(t_ast_redir_list *redir_list)
{
	assert(redir_list != NULL);
	vector_init(redir_list, sizeof(t_ast_redirection), 0);
}

void	ast_redir_list_free(t_ast_redir_list *redir_list)
{
	assert(redir_list != NULL);
	vector_free(redir_list, ast_redirection_free);
}
