#include <stdlib.h>
#include "lexer.h"

void	lexer_input_stack_init(t_lexer_input_stack *stack)
{
	vector_init(stack, sizeof(t_lexer_input_stack_item *), 0);
}

void	lexer_input_stack_free(t_lexer_input_stack *stack)
{
	vector_free(stack, lexer_input_stack_item_free);
}

t_error	lexer_input_stack_item_init(t_lexer_input_stack_item **item)
{
	*item = malloc(sizeof(t_lexer_input_stack_item));
	if (*item == NULL)
		return (error_sys());
	**item = (t_lexer_input_stack_item){0};
	context_stack_init(&(*item)->context);
	return (error(ERR_NO));
}

void	lexer_input_stack_item_free(void *item)
{
	t_lexer_input_stack_item	**item_;

	item_ = (t_lexer_input_stack_item **)item;
	string_free(&(*item_)->str);
	ft_bzero((*item_)->context.data, (*item_)->context.cap);
	vector_free(&(*item_)->context, NULL);
	**item_ = (t_lexer_input_stack_item){0};
	free(*item_);
	*item_ = NULL;
}
