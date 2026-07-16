#include "lexer.h"
# include <assert.h>

void	lexer_input_stack_pop(t_lexer_input_stack *stack)
{
	t_lexer_input_stack_item	*last_item;

	assert(stack->len > 0);
	(void)vector_pop(stack, (void **)&last_item);
	lexer_input_stack_item_free(&last_item);
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

t_error	lexer_input_stack_dup(
			t_lexer_input_stack *out,
			const t_lexer_input_stack *in)
{
	size_t						i;
	t_error						err;
	t_string					str;
	t_lexer_input_stack_item	*item;
	t_lexer_input_stack_item	*item_dup;	

	i = 0;
	lexer_input_stack_init(out);
	while (i < in->len)
	{
		err = lexer_input_stack_item_init(&item_dup);
		if (err.type)
			return (lexer_input_stack_free(out), err);
		item = ((t_lexer_input_stack_item **)in->data)[i++];
		str = item->str;
		item_dup->i = item->i;
		if (!string_init(&item_dup->str, 0, str.data, (long)str.len))
		{
			err = error_sys();
			lexer_input_stack_item_free(&item_dup);
			return (lexer_input_stack_free(out), err);
		}
		lexer_input_stack_push(out, item_dup);
	}
	return (error(ERR_NO));
}
