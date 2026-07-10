#include "parser_type.h"
#include <stdlib.h>
#ifdef DEBUG_PARSING
# include <stdio.h>	// DEBUG
# include "logs.h"	// DEBUG
#endif

static inline void	update_parser_bools(t_parser *parser)
{
	parser->assignment_disabled = parser->function_body_depth > 0;
	parser->expansion_disabled = parser->function_body_depth > 0;
}

t_error	hook_9_increment(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	(void)rhs;
	(void)len;
	(void)lhs;
	parser->function_body_depth++;
	update_parser_bools(parser);
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] %sfunction_body_depth = %zu%s\n", YELLOW, parser->function_body_depth, NC);
#endif
	return (error(ERR_NO));
}

t_error	hook_9_decrement(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	(void)rhs;
	(void)len;
	(void)lhs;
	if (parser->function_body_depth == 0)
		return (error_print(
			error(ERR_PARSER_INVALID_STATE),
			"parser",
			"function_body_depth is already 0",
			NULL,
			NULL));
	parser->function_body_depth--;
	update_parser_bools(parser);
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] %sfunction_body_depth = %zu%s\n", YELLOW, parser->function_body_depth, NC);
#endif
	return (error(ERR_NO));
}
