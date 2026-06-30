#include "expander_expansion_.h"

void	expansion_init(t_expansion *expansion)
{
	*expansion = (t_expansion){0};
	vector_init(expansion, sizeof(t_string), 0);
}

void	expansion_free(t_expansion *expansion)
{
	vector_free(expansion, string_free_void);
	*expansion = (t_expansion){0};
}
