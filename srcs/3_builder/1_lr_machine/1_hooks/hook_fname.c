#include "parser.h"
#include "token.h"
#include "utils.h"
#include "hooks.h"
# include "logs.h"	// DEBUG
# include <assert.h>

t_error	hook_fname(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	t_token		*token;
	t_error		err;

	assert(parser != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);
	assert(len == 1);
	if (len != 1)
		return (error_print(error(ERR_HOOK_INVALID_RHS_LEN), __func__,
			NULL, "expected 1 received %i", (int)len));
	err = parser_get_token(__func__, parser, rhs[0].tokens_start_id, &token);
	if (err.type)
		return (err);
	if (!name_is_valid(&token->value))
		err = error_print(error(ERR_POSIX_SYNTAX),
			"parser", "invalid function name", NULL, "%s", token->value.data);
#ifdef DEBUG_PARSING
	else
		fprintf(stderr, "[PARSER] %sfunction name is valid%s\n", YELLOW, NC);
#endif
	if (err.type != ERR_NO)
		return (err);
	return (hook_9_increment(parser, rhs, len, lhs));
}
