#include "parser.h"
# include <assert.h>	// DEBUG

t_error	parser_get_token(
			const char *caller,
			const t_parser *parser,
			size_t index,
			t_token **out)
{
	assert(caller != NULL);
	assert(parser != NULL);
	assert(index < parser->tokens.len);
	assert(out != NULL);
	if (index >= parser->tokens.len)
		return (error_print(error(ERR_INDEX_OUT_OF_BOUND), "parser", caller,
			"Unable to get heredoc delimiter token", NULL, NULL));
	*out = &((t_token *)parser->tokens.data)[index];
	return (error(ERR_NO));
}
