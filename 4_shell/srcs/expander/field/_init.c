#include "field_.h"

void	fields_init(t_fields *fields)
{
	vector_init(fields, sizeof(t_word), 0);
}

void	fields_free(t_fields *fields)
{
	vector_free(fields, (void (*)(void *))word_free);
}
