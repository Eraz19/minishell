#include "ast_type.h"
#include "converter_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	ast_redirection_init(t_ast_redirection *redirection)
{
	assert(redirection != NULL);
	redirection->operation = AST_REDIR_COUNT;
	redirection->expand_heredoc_body = false;
	redirection->fd = -1;
	redirection->word = NULL;
	(void)string_init(&redirection->expanded_word, 0, NULL, 0);
	redirection->is_location = false;
	redirection->location = NULL;
	(void)string_init(&redirection->expanded_location, 0, NULL, 0);
}

void	ast_redirection_free(void *redirection)
{
	t_ast_redirection	*redir;

	assert(redirection != NULL);
	redir = (t_ast_redirection *)redirection;
	redir->operation = AST_REDIR_COUNT;
	redir->expand_heredoc_body = false;
	redir->fd = -1;
	if (redir->operation == AST_REDIR_HEREDOC)
	{
		token_free(redir->word);
		free(redir->word);
	}
	redir->word = NULL;
	string_free(&redir->expanded_word);
	redir->is_location = false;
	redir->location = NULL;
	string_free(&redir->expanded_location);
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
