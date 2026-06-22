#include "parser_type.h"
#include "qualifiers_priv.h"
#include "utils.h"
#include <stdlib.h>

// TODO: Ask to Alexander to implement it in scanner's token module
static bool	token_contains_unquoted_equal(const char *token)
{
	(void)token;
	// TODO: "If the TOKEN contains an unquoted (as determined while applying rule 4 from 2.3 Token Recognition) <equals-sign> character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct (as determined while applying rule 5 from 2.3 Token Recognition):"
	return (false);
}

t_error		qualify_7b(void *parser, const char *token_value)
{
	t_parser	*parser_;
	char		*name;
	char		*value;
	t_error		err;

	parser_ = (t_parser *)parser;
	if (token_contains_unquoted_equal(token_value) && token_value[0] != '=')
	{
		/*
		* TODO:
		* 	assignment_split() should follow these POSIX conditions:
		*		"If the TOKEN contains an unquoted (as determined while applying rule 4 from 2.3 Token Recognition) <equals-sign> character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct (as determined while applying rule 5 from 2.3 Token Recognition):"
		*/
		err = assignment_split(token_value, &name, &value);
		if (err.type != ERR_NO)
			return (err);
		if (name_is_valid(name) && !parser_->assignment_disabled)
			parser_->lookahead_symbol = SYM_ASSIGNMENT_WORD;
		else
			parser_->lookahead_symbol = SYM_WORD;
		free(name);
		if (value)
			free(value);
	}
	else
		parser_->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
