#include "lexer.h"
# include <assert.h>

void	lexer_input_stack_pop(t_lexer_input_stack *stack)
{
	t_lexer_input_stack_item	*last_item;

<<<<<<< HEAD
	assert(stack->len > 0);
	(void)vector_pop(stack, (void **)&last_item);
	lexer_input_stack_item_free(&last_item);
=======
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(stack, stack->len - 1, (void **)&last_item))
		return (error(ERR_INDEX_OUT_OF_BOUND));
	return (lexer_input_stack_item_free(&last_item), error(ERR_NO));
>>>>>>> a1ba55e6c4e2aa89a165770689bc902317a45b72
}

t_error	lexer_input_stack_push(
			t_lexer_input_stack *stack,
			t_lexer_input_stack_item *item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	lexer_input_stack_get_last(
			t_lexer_input_stack *stack,
			t_lexer_input_stack_item **item)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	*item = ((t_lexer_input_stack_item **)stack->data)[stack->len - 1];
	return (error(ERR_NO));
}
