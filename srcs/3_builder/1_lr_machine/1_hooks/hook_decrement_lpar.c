#include "error.h"
#include "parser_type.h"
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	hook_decrement_lpar(
			t_parser *parser,
			t_parser_item *rhs,
			size_t len,
			t_parser_item *lhs)
{

	assert(parser != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);
	(void)len;
	if (parser->search_cmd_sub_end == false)
		return (error(ERR_NO));
	parser->opening_par--;
	// fprintf(stderr, "%s[PARSER] %s() => opening_par decremented to %zu%s\n",
	// 	YELLOW, __func__, parser->opening_par, NC);
	return (error(ERR_NO));
}
