#include "ast.h"
#include "heredoc.h"
# include <assert.h>	// DEBUG

void	ast_redirection_init(t_ast_redirection *redirection)
{
	assert(redirection != NULL);
	redirection->operation = AST_REDIR_COUNT;
	redirection->expand_heredoc_body = false;
	redirection->fd = -1;
	token_init(&redirection->word);
	redirection->is_location = false;
	token_init(&redirection->location);
}

void	ast_redirection_free(void *redirection)
{
	t_ast_redirection	*redir;

	assert(redirection != NULL);
	redir = (t_ast_redirection *)redirection;
	if (redir->operation == AST_REDIR_HEREDOC && redir->word.value.data != NULL)
		heredoc_unlink(redir->word.value.data);
	token_free(&redir->word);
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
