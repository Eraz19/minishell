#include "quote_removal_.h"
#include "expander_loader_.h"
#include "field_splitting_.h"
#include "path_name_expansion.h"
#include "expander_substitutions.h"

t_error	expander_expand_word(char ***expansion, t_expander_args *args)
{
	t_expander	state;

	expander_init(&state, args->role);
	if (expander_load(&state, args->value, args->contexts).type)
		return (expander_free(&state), state.err);
	if (substitutions(&state).type)
		return (expander_free(&state), state.err);
	if (field_splitting(&state).type)
		return (expander_free(&state), state.err);
	if (path_name_expansion(&state).type)
		return (expander_free(&state), state.err);
	if (quote_removal(&state).type)
		return (expander_free(&state), state.err);
	state.err = expander_loader_extract(&state.fields, expansion);
	return (expander_free(&state), state.err);
}
