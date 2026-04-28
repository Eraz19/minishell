#ifndef PARSER_QUALIFIER_H
# define PARSER_QUALIFIER_H

# include "lexer.h"		// t_token
# include "parser.h"	// t_parser

// ---------- Public ----------

bool	qualify_token(t_parser *parser, t_token *token);

// ---------- Private ----------

/* REQUIREMENTS
token.id == WORD
&& token.value is in [<resserved_words>]
&& (
	is the first word of command
	|| (previous word is reserved && previous word is NOT in [case, for, in])
	|| (is the third word && first word == "case" && token.value == "in")
	|| (is the third word && first word == "for" && token.value == "in" or "do")
)
*/
bool	qualify_as_reserved(t_parser *parser, t_token *token);

// Utilities
size_t	get_word_position(t_parser *parser);
t_token	*get_previous_word(t_parser *parser);
t_token	*get_first_word(t_parser *parser);

#endif
