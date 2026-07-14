#include "libft.h"
#include "error.h"
#include "parser_type.h"
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
	if (!vector_push(&parser->here_stack, &rhs->cst_node))
		return (error_sys());
	return (error(ERR_NO));
}
