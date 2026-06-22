#include "parser_type.h"
#include <stdlib.h>

static inline void	update_parser_bools(t_parser *parser)
{
	parser->assignment_disabled = parser->function_body_depth > 0;
	parser->expansion_disabled = parser->function_body_depth > 0;
}

# include <stdio.h>
t_error	hook_9_increment(t_parser_stack_item *rhs, size_t len, void *ctx)
{
	t_parser	*parser;

	(void)rhs;
	(void)len;
	parser = (t_parser *)ctx;
	parser->function_body_depth++;
	update_parser_bools(parser);
	printf("----------\n");
	printf ("[PARSER] [%s] function_body_depth = %zu\n", __func__, parser->function_body_depth);
	printf("----------\n");
	return (error(ERR_NO));
}

t_error	hook_9_decrement(t_parser_stack_item *rhs, size_t len, void *ctx)
{
	t_parser	*parser;

	(void)rhs;
	(void)len;
	parser = (t_parser *)ctx;
	if (parser->function_body_depth == 0)
		return (error_print(
			error(ERR_PARSER_INVALID_STATE),
			"parser",
			"function_body_depth is already 0",
			NULL,
			NULL));
	parser->function_body_depth--;
	update_parser_bools(parser);
	printf("----------\n");
	printf ("[PARSER] [%s] function_body_depth = %zu\n", __func__, parser->function_body_depth);
	printf("----------\n");
	return (error(ERR_NO));
}
