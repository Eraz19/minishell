#include "parser.h"
#include "token.h"
#include "utils.h"
#include "hooks.h"
#ifdef DEBUG_PARSING
# include "logs.h"	// DEBUG
#endif
# include <assert.h>

t_error	hook_fname(
			t_parser *parser,
			t_parser_item *rhs,
			size_t len,
			t_parser_item *lhs)
{
	t_token		*token;

	assert(parser != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);
	assert(len == 1);
	token = parser_get_token(parser, rhs[0].tokens_start_id);
	if (!name_is_valid_str(&token->value))
		return (error_print(error(ERR_POSIX_SYNTAX),
			"parser", "invalid function name", NULL, "%s", token->value.data));
#ifdef DEBUG_PARSING
	else
		fprintf(stderr, "[PARSER] %sfunction name is valid%s\n", YELLOW, NC);
#endif
	return (error(ERR_NO));
}
