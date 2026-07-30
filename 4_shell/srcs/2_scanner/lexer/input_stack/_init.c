#include "lexer_input_stack.h"

void	lexer_input_stack_init(t_lexer_input_stack *stack)
{
	vector_init(stack, sizeof(t_lexer_input_stack_item), 0);
}

void	lexer_input_stack_free(t_lexer_input_stack *stack)
{
	vector_free(stack, lexer_input_stack_item_free);
}
