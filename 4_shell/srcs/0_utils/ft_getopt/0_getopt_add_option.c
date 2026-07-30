#include "ft_getopt_priv.h"

t_error	getopt_add_option(t_getopt_state *state, t_getopt_option *src)
{
	if (!vector_push(&state->out->options, src))
		return (error_sys());
	return (error(ERR_NO));
}
