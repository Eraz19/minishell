#include "cmd_assignator_priv.h"
# include <assert.h>	// DEBUG

t_error	cmd_assignment_expand(
			const t_token *token,
			t_exp_flag flags,
			t_string *out_expanded)
{
	t_expansion	expansion;
	t_error		err;

	err = expand_token(&expansion, token, flags);
	if (err.type)
		return (err);
	assert(expansion.len == 1);
	err = expansion_take(&expansion, 0, out_expanded);
	expansion_free(&expansion);
	assert(token->assignment_offset >= 0);
	assert((size_t)token->assignment_offset < out_expanded->len);
	assert(out_expanded->data[token->assignment_offset] == '=');
	return (err);
}
