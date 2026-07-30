#include "lexer_priv.h"

t_error	bind_lexer_input(t_lexer *lexer, t_string *input)
{
	t_lexer_input_stack_item	item;

	if (input != NULL)
	{
		lexer_input_stack_item_init(&item);
		string_take_string(&item.str, input);
		lexer->err = lexer_input_stack_push(&lexer->input_stack, &item);
		if (lexer->err.type)
			return (string_take_string(input, &item.str), lexer->err);
	}
	lexer_input_stack_get_last(&lexer->input_stack, &lexer->input);
	return (lexer->err);
}
