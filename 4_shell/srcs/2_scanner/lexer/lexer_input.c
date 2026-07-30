#include "lexer_priv.h"

void	bind_lexer_input(t_lexer *lexer)
{
	lexer_input_stack_get_last(&lexer->input_stack, &lexer->input);
}
