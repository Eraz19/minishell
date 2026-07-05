#include "redirector_priv.h"
#include "expander.h"
#include "heredoc.h"

// @ret TODO (heredoc_expand() has no doc yet)
static inline t_error	redirect_expand_heredoc_body(t_ast_redirection *redir)
{
	if (redir->expand_heredoc_body)
		return (heredoc_expand_body(&redir->word->value));
	return (error(ERR_NO));
}

// @ret TODO (expander has no doc yet)
static inline t_error	redirect_expand_word(
							const char *param_name,
							t_token *token,
							t_exp_flag flags,
							t_string *out_string)
{
	t_expansion	expansion;
	t_error		err;

	err = expand_token(&expansion, token, flags);
	if (err.type)
		return (err);
	else if (expansion.len == 0 || expansion.len > 1)
	{
		expansion_free(&expansion);
		return (error_print(error(ERR_REDIRECTION_FAILED), REDIRECTOR_MODULE_NAME,
			param_name, " does not expand to exactly one field",
			NULL, "%s", token->value.data));
	}
	err = expansion_take(&expansion, 0, out_string);
	expansion_free(&expansion);
	return (err);
}

t_error	redirect_expand(t_ast_redirection *redirection)
{
	t_exp_flag	flags;
	t_error		err;

	flags = EXP_TILDE | EXP_PARAM | EXP_CMD_SUB | EXP_ARITH | EXP_QUOTE_REMOVAL;
	if (redirection->operation == AST_REDIR_HEREDOC)
		err = redirect_expand_heredoc_body(redirection);
	else
		err = redirect_expand_word(
				"word",
				redirection->word,
				flags,
				&redirection->expanded_word);
	if (err.type == ERR_NO && redirection->is_location)
		err = redirect_expand_word(
				"io_location",
				redirection->location,
				flags,
				&redirection->expanded_location);
	return (err);
}
