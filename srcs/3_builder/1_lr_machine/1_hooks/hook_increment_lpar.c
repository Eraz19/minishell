#include "error.h"
#include "parser_type.h"
#include "parser.h"
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	hook_increment_lpar(
			t_parser *parser,
			t_parser_item *rhs,
			size_t len,
			t_parser_item *lhs)
{
	t_token	*token;

	assert(parser != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);
	if (len != 2 || parser->search_cmd_sub_end == false)
		return (error(ERR_NO));
	token = parser_get_token(parser, rhs[0].tokens_start_id);
	if (token->type == TOKEN_LPARENTHESIS)
	{
		parser->opening_par++;
		fprintf(stderr, "%s[PARSER] %s() => opening_par decremented to %zu%s\n",
			YELLOW, __func__, parser->opening_par, NC);
	}
	return (error(ERR_NO));
}
