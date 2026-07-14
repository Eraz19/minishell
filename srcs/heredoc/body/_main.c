#include <fcntl.h>
#include "body_.h"

t_lexer_context_args	body_context_rules(void)
{
	t_lexer_context_args	res;

	res.quoting = NULL;
	res.is_quoting = NULL;
	res.unescaped_args = NULL;
	res.escape = body_escape;
	res.is_end = is_context_none_ending;
	res.unescaped = body_unescape;
	res.expansion = lexer_rule_expansion;
	res.is_expansion = is_substitution_context;
	return (res);
}
