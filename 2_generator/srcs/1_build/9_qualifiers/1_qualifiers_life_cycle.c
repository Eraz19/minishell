#include "generator_qualifiers.h"
#include <stdlib.h>

void	qualifiers_init(t_qualifier **qualifiers)
{
	*qualifiers = NULL;
}

void	qualifiers_free(t_qualifier **qualifiers)
{
	if (!qualifiers || !*qualifiers)
		return ;
	free(*qualifiers);
	*qualifiers = NULL;
}
