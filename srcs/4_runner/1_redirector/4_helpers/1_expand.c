#include "redirector_priv.h"
#include "expander.h"
#include "cmd_expansion.h"

#define CITATION_1		"POSIX 2.10.2: The expansions specified in 2.7 "
#define CITATION_2		"Redirection shall occur. As specified there, exactly "
#define CITATION_3		"one field can result (or the result is unspecified)"
#define CITATION		CITATION_1 CITATION_2 CITATION_3

// @ret ERR_POSIX_EXPANSION / ERR_REDIRECTION / ERR_INTERNAL / ERR_LIBC
static inline t_error	redirect_expand_word(
							t_token *token,
							t_string *out,
							int *exit_status)
{
	t_exp_flag	flags;
	t_expansion	expansion;
	t_error		err;

	flags = cmd_redirection_expansion_flags();
	err = expand_token(&expansion, token, exit_status, flags);
	if (err.type)
		return (err);
	else if (expansion.len != 1)
		return (expansion_merge(token->value.data, CITATION, &expansion, out));
	err = expansion_take(&expansion, 0, out);
	expansion_free(&expansion);
	return (err);
}

t_error	redirect_expand(t_redir *redir, int *exit_status)
{
	t_exp_flag	flags;
	t_error		err;

	if (redir->operation == AST_REDIR_HEREDOC)
	{
		flags = cmd_heredoc_body_expansion_flags();
		if (redir->expand_heredoc_body)
			return (expand_str(&redir->expanded_word, redir->heredoc_body,
						exit_status, flags));
		else if (!string_dup(&redir->expanded_word, redir->heredoc_body))
			return (error_sys());
	}
	else
		err = redirect_expand_word(&redir->word, &redir->expanded_word,
				exit_status);
	if (err.type == ERR_NO && redir->is_location)
		err = redirect_expand_word(&redir->location, &redir->expanded_location,
				exit_status);
	return (err);
}
