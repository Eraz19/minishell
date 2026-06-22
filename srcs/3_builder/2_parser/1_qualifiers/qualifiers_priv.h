#ifndef QUALIFIERS_PRIV_H
# define QUALIFIERS_PRIV_H

# include "error.h"
# include "symbols_type.h"
# include <stddef.h>

/*
* @note Qualifier 3 is partially applied via reduce_hook hook_3()
* @note Qualifier 9 is applied via reduce_hooks hook_9_increment() and hook_9_decrement()
*/
typedef enum qualifier_id
{
	QUALIFIER_NONE,
	QUALIFIER_WORD,
	QUALIFIER_1,
	QUALIFIER_2,
	QUALIFIER_3,
	QUALIFIER_4,
	QUALIFIER_5,
	QUALIFIER_6A,
	QUALIFIER_6B,
	QUALIFIER_7A,
	QUALIFIER_7B,
	QUALIFIER_8,
	QUALIFIER_COUNT
}	t_qualifier_id;

bool		qualify_try_reserved_word(
	const char *token_value,
	t_symbol *dst_symbol);
bool		qualify_try_name(const char *token_value, t_symbol *dst_symbol);
t_error		qualify_word(void *parser, const char *token_value);
t_error		qualify_1(void *parser, const char *token_value);
t_error		qualify_2(void *parser, const char *token_value);
t_error		qualify_4(void *parser, const char *token_value);
t_error		qualify_5(void *parser, const char *token_value);
t_error		qualify_6a(void *parser, const char *token_value);
t_error		qualify_6b(void *parser, const char *token_value);
t_error		qualify_7a(void *parser, const char *token_value);
t_error		qualify_7b(void *parser, const char *token_value);
t_error		qualify_8(void *parser, const char *token_value);

#endif
