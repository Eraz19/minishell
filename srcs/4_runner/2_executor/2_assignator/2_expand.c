#include "cmd_assignator_priv.h"
# include <assert.h>	// DEBUG

#define CITATION_1	"POSIX 2.9.1.1: Each variable assignment shall be expanded "
#define CITATION_2	"for [...] but no field splitting -> POSIX 2.6: [...] shall"
#define CITATION_3	" expand to a single field"
#define CITATION	CITATION_1 CITATION_2 CITATION_3

t_error	cmd_assignment_expand(
			const t_token *token,
			t_exp_flag flags,
			t_string *out,
			int *exit_status)
{
	t_expansion	expansion;
	t_error		err;

	err = expand_token(&expansion, token, exit_status, flags);
	if (err.type)
		return (err);
	if (expansion.len != 1)
		return (expansion_merge(token->value.data, CITATION, &expansion, out));
	err = expansion_take(&expansion, 0, out);
	expansion_free(&expansion);
	assert(token->assignment_offset >= 0);
	assert((size_t)token->assignment_offset < out->len);
	assert(out->data[token->assignment_offset] == '=');
	return (err);
}
