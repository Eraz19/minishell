#ifndef QUALIFIERS_PRIV_H
# define QUALIFIERS_PRIV_H

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
					t_symbol *out_symbol);
bool			qualify_try_name(const t_token *token, t_symbol *dst_symbol);
void			qualify_word(const t_token *token, t_symbol *out_symbol);
void			qualify_1(const t_token *token, t_symbol *out_symbol);
void			qualify_2(const t_token *token, t_symbol *out_symbol);
void			qualify_4(const t_token *token, t_symbol *out_symbol);
void			qualify_5(const t_token *token, t_symbol *out_symbol);
void			qualify_6a(const t_token *token, t_symbol *out_symbol);
void			qualify_6b(const t_token *token, t_symbol *out_symbol);
void			qualify_7a(const t_token *token, t_symbol *out_symbol);
void			qualify_7b(const t_token *token, t_symbol *out_symbol);

// Build helpers

bool			qualifier_should_apply_word(
					const t_lr_machine *machine,
					size_t lr_state_id);
bool			qualifier_should_apply_1(
					const t_lr_machine *machine,
					size_t lr_state_id);
bool			qualifier_rule_is_at_target(
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
