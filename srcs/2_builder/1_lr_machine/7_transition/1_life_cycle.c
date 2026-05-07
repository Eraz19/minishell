#include "parser.h"

void	transition_init(t_vector *transitions)
{
	vector_init(transitions, sizeof(t_transition), 0);
}

void	transition_free(t_vector *transitions)
{
	vector_free(transitions);
}
