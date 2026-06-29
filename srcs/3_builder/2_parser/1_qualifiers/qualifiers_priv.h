#ifndef QUALIFIERS_PRIV_H
# define QUALIFIERS_PRIV_H

# include "error.h"
# include "token.h"
# include "lr_machine_type.h"
# include "rule_state_type.h"
# include "symbols_type.h"
# include <stddef.h>

/*
** @note Qualifier 3 is partially applied via reduce_hook hook_3()
** @note Qualifier 8 has been disabled since fname has been replaced by 
**		WORD in grammar (name validation is now applied on 
**		function_definition reduction)
** @note Qualifier 9 is applied via reduce_hooks hook_9_increment()
**		and hook_9_decrement()
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

bool			qualify_try_reserved_word(
					const t_token *token,
					t_symbol *dst_symbol);
bool			qualify_try_name(const t_token *token, t_symbol *dst_symbol);
t_error			qualify_word(void *parser, const t_token *token);
t_error			qualify_1(void *parser, const t_token *token);
t_error			qualify_2(void *parser, const t_token *token);
t_error			qualify_4(void *parser, const t_token *token);
t_error			qualify_5(void *parser, const t_token *token);
t_error			qualify_6a(void *parser, const t_token *token);
t_error			qualify_6b(void *parser, const t_token *token);
t_error			qualify_7a(void *parser, const t_token *token);
t_error			qualify_7b(void *parser, const t_token *token);

// Build helpers

bool			should_apply_qualifier_word(
					const t_lr_machine *machine,
					size_t lr_state_id);
bool			should_apply_qualifier_1(
					const t_lr_machine *machine,
					size_t lr_state_id);
bool			rule_is_at_target(
					const t_rule_state *rule_state,
					t_rule_id rule_id,
					size_t target_pos);
t_qualifier_id	qualifier_default_id(
					const t_lr_machine *machine,
					const t_rule_state *rule_state);
t_qualifier_id	qualifier_6_choose_variant(
					const t_lr_machine *machine,
					size_t lr_state_id);

#endif
