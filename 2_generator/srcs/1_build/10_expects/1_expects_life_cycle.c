#include "generator_expects.h"
#include <stdlib.h>

void	expects_init(bool **expects)
{
	*expects = NULL;
}

void	expects_free(bool **expects)
{
	if (!expects || !*expects)
		return ;
	free(*expects);
	*expects = NULL;
}
