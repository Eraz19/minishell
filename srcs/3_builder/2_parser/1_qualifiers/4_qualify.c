#include "parser_type.h"
#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

t_error		qualify_4(void *parser, const t_token *token)
{
	assert(parser != NULL);
	assert(token != NULL);
	if (str_cmp("esac", token->value.data) == 0)
		((t_parser *)parser)->lookahead_symbol = SYM_Esac;
	else
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
