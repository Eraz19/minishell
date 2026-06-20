#include "error.h"
#include "expander_.h"
#include <stdbool.h>

bool	builder_can_next_word_be_a_cmd_name(void)
{
	return (true);
}

t_error	path_name_expansion(t_expander *state)
{
	(void)state;
	return (error(ERR_NO));
}

t_error	substitutions(t_expander *state)
{
	(void)state;
	return (error(ERR_NO));
}
