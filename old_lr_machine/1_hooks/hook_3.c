#include "libft.h"
#include "error.h"
#include "parser_type.h"
#include "parser.h"
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	hook_3(
			t_parser *parser,
			t_parser_item *rhs,
			size_t len,
			t_parser_item *lhs)
{
	assert(parser != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);
	assert(len == 2);
	if (!vector_push(&parser->here_stack, &lhs->cst_node))
		return (error_sys());
	fprintf(stderr, "%s[PARSER] heredoc registered (%s%s%s)%s\n",
		YELLOW, BLUE, parser_get_token(parser, rhs[1].tokens_start_id)->value.data, YELLOW, NC);
	return (error(ERR_NO));
}
