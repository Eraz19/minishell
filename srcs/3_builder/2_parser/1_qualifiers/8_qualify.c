#include "parser_type.h"
#include "qualifiers_priv.h"

# include "utils.h"	// DEBUG
# include <stdio.h>	// DEBUG
t_error		qualify_8(void *parser, const char *token_value)
{
	t_parser	*parser_;

	parser_ = (t_parser *)parser;
	fprintf(stderr, "[QUALIFIER 8] value=%s valid_name=%d disabled_assign=%d\n",
		token_value,
		name_is_valid(token_value),
		parser_->assignment_disabled);
	if (qualify_try_reserved_word(token_value, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	else if (qualify_try_name(token_value, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	return (qualify_7a(parser, token_value));
}
