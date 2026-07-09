#include "heredoc_.h"
#include "expander.h"

t_error	expand_delim(t_heredoc *heredoc, t_string *out, const t_token *delim)
{
	t_expansion	exp;
	t_string	delim_exp;

	heredoc->err = expand_token(&exp, delim, EXP_QUOTE_REMOVAL);
	if (heredoc->err.type)
		return (heredoc->err);
	if (exp.len != 1)
		return (expansion_free(&exp),
			heredoc->err = error(ERR_EXP_RESULT_INCOHERENT));
	heredoc->err = expansion_get(&delim_exp, &exp, 0);
	if (heredoc->err.type)
		return (expansion_free(&exp), heredoc->err);
	if (!string_init(out, 0, delim_exp.data, -1))
		return (heredoc->err = error_sys(), expansion_free(&exp), heredoc->err);
	if (!string_append_n(out, "\n", 1))
	{
		heredoc->err = error_sys();
		return (string_free(out), expansion_free(&exp), heredoc->err);
	}
	return (expansion_free(&exp), heredoc->err);
}

uint	generate_heredoc_body_expand_flags(void)
{
	return (EXP_PARAM
		| EXP_CMD_SUB
		| EXP_ARITH
		| EXP_QUOTE_REMOVAL);
}
