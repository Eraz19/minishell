#include "specials.h"
#include <stdlib.h>

void	specials_init(t_specials *specials)
{
	specials->zero = NULL;
	specials->source = NULL;
	specials->positional_params = NULL;
	specials->positional_count = 0;
	specials->pid = -1;
	specials->last_bg_pid = -1;
	specials->last_status = 0;
}

void	specials_free(t_specials *specials)
{
	specials_init(specials);
}
