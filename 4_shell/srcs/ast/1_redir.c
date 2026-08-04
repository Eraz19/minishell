#include "ast.h"
#include "utils.h"
#include <assert.h>	// DEBUG

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

t_error	ast_redirection_dup(void *dst, const void *src)
{
	t_ast_redirection		*dst_redirection;
	const t_ast_redirection	*src_redirection;
	t_error					err;

	dst_redirection = (t_ast_redirection *)dst;
	src_redirection = (const t_ast_redirection *)src;
	ast_redirection_init(dst_redirection);
	dst_redirection->operation = src_redirection->operation;
	dst_redirection->fd = src_redirection->fd;
	dst_redirection->expand_heredoc_body = src_redirection->expand_heredoc_body;
	dst_redirection->is_location = src_redirection->is_location;
	err = token_dup(&dst_redirection->word, &src_redirection->word);
	if (err.type == ERR_NO && !string_dup(&dst_redirection->heredoc_body,
		&src_redirection->heredoc_body))
		err = error_sys();
	if (err.type == ERR_NO)
		err = token_dup(&dst_redirection->location, &src_redirection->location);
	if (err.type)
		return (ast_redirection_free(dst_redirection), err);
	return (error(ERR_NO));
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

t_error	ast_redir_list_dup(void *dst, const void *src)
{
	return (vector_deep_dup(dst, src, ast_redirection_dup,
				ast_redirection_free));
}

void	ast_redir_list_free(t_ast_redir_list *redir_list)
{
	assert(redir_list != NULL);
	vector_free(redir_list, ast_redirection_free);
}
