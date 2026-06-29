#include "error.h"
#include "expander_.h"
#include <stdbool.h>

/* ---------- TODO: shell ---------- */

t_error		shell_should_interrupt(bool *out)
{
	*out = true;
	return (error(ERR_NO));
}

/* ---------- TODO: expander ---------- */
