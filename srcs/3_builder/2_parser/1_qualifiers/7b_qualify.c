#include "parser_type.h"
#include "qualifiers_priv.h"
#include "utils.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG
# include <assert.h>	// DEBUG

t_error		qualify_7b(void *parser, const t_token *token)
{
	t_parser	*parser_;
	t_string	truncated;

	assert(parser != NULL);
	assert(token != NULL);
	parser_ = (t_parser *)parser;
	truncated.data = token->value.data;
	truncated.cap = token->value.cap;
	truncated.len = (size_t)token->assignment_offset + 1;
	if (!parser_->assignment_disabled
		&& token->assignment_offset != -1
		&& name_is_valid(&truncated))
		parser_->lookahead_symbol = SYM_ASSIGNMENT_WORD;
	else
		parser_->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
