#include "error.h"
#include "parser_type.h"
#include "parser.h"
#ifdef DEBUG_CMD_SUB
# include "debug.h"		// DEBUG
#endif
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	hook_cmd_sub(
			t_parser *parser,
			t_parser_item *rhs,
			size_t len,
			t_parser_item *lhs)
{
	t_token	*closing_par_token;

	assert(parser != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);
	assert(len == 3);
	if (parser->search_cmd_sub_end == false)
		return (error(ERR_NO));
	parser->opening_par--;
#ifdef DEBUG_CMD_SUB
	fprintf(stderr, YELLOW "%s() search_cmd_sub_end=%s opening_par=%zu\n" NC,
		__func__, bool_to_string(parser->search_cmd_sub_end), parser->opening_par);
#endif
	if (parser->opening_par > 0)
		return (error(ERR_NO));
	closing_par_token = parser_get_token(parser, rhs[2].tokens_start_id);
	assert(closing_par_token != NULL);
	parser->cmd_sub_end_index = closing_par_token->index.end;
	fprintf(stderr, "%s[PARSER] cmd sub end found at index %zu%s\n",
		YELLOW, parser->cmd_sub_end_index, NC);
	return (error(ERR_CMD_SUB_END_FOUND));
}
