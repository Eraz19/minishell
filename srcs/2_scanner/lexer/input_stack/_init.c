#include <stdlib.h>
#include "input_stack_.h"

void	input_parser_stack_item_free(void *item)
{
	t_input_parser_stack_item	**item_;

	item_ = (t_input_parser_stack_item **)item;
	if ((*item_)->str != NULL)
		free((*item_)->str);
	ft_bzero((*item_)->context.data, (*item_)->context.cap);
	vector_free(&(*item_)->context, NULL);
	**item_ = (t_input_parser_stack_item){0};
	free(*item_);
	*item_ = NULL;
}

t_error	input_parser_stack_item_init(t_input_parser_stack_item **item)
{
	*item = malloc(sizeof(t_input_parser_stack_item));
	if (*item == NULL)
		return (error_sys());
	**item = (t_input_parser_stack_item){0};
	context_stack_init(&(*item)->context);
	return (error(ERR_NO));
}

void	input_stack_init(t_input_stack *stack)
{
	vector_init(stack, sizeof(t_input_parser_stack_item *), 0);
}

void	input_stack_free(t_input_stack *stack)
{
	vector_free(stack, input_parser_stack_item_free);
}
