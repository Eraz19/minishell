#include "heredoc_.h"
#include "expander.h"

t_error	expand_delim(t_heredoc *heredoc, t_string *out, const t_token *delim)
{
	int	exit_status;

	heredoc->err = expand_token_merged(
						out,
						delim,
						&exit_status,
						EXP_QUOTE_REMOVAL);
	if (heredoc->err.type)
		return (heredoc->err);
	if (!string_append_n(out, "\n", 1))
		return (heredoc->err = error_sys(), string_free(out), heredoc->err);
	return (error(ERR_NO));
}

uint	generate_heredoc_body_expand_flags(void)
{
	return (EXP_PARAM
		| EXP_CMD_SUB
		| EXP_ARITH
		| EXP_QUOTE_REMOVAL
		| EXP_HEREDOC);
}
