#include "error.h"
#include "expander.h"
#include "expander_.h"
#include "quote_removal_.h"
#include "field_splitting_.h"
#include "expander_loader_.h"
#include "path_name_expansion_.h"
#include "expander_substitutions_.h"

t_error	expander_expand(t_expansion *expansion, t_expander_args *args)
{
	t_expander	state;

	expander_init(&state);
	if (expander_load(&state, args).type)
		return (expander_free(&state), state.err);
	if (substitutions(&state).type)
		return (expander_free(&state), state.err);
	if (flag_is_active((uint)state.flags, EXP_FIELD_SPLIT))
	{
		if (field_splitting(&state).type)	
			return (expander_free(&state), state.err);
	}
	if (flag_is_active((uint)state.flags, EXP_PATH_NAME))
	{
		if (path_name_expansion(&state).type)
			return (expander_free(&state), state.err);
	}
	if (flag_is_active((uint)state.flags, EXP_QUOTE_REMOVAL))
	{
		if (quote_removal(&state).type)
			return (expander_free(&state), state.err);
	}
	state.err = expander_loader_extract(&state.fields, expansion);
	return (expander_free(&state), state.err);
}
