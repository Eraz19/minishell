#include "cmd.h"
#include "cmd_priv.h"
#include "tokens.h"
#include "expander.h"

static inline t_exp_flag	cmd_regular_expansion_flags(void)
{
	return (EXP_TILDE_NORMAL | EXP_PARAM | EXP_CMD_SUB | EXP_ARITH
		| EXP_FIELD_SPLIT | EXP_PATH_NAME | EXP_QUOTE_REMOVAL);
}

static inline t_exp_flag	cmd_assignment_expansion_flags(void)
{
	return (EXP_TILDE_ASSIGNMENT | EXP_PARAM | EXP_CMD_SUB | EXP_ARITH
		| EXP_QUOTE_REMOVAL);
}

static inline void	cmd_compute_name(
						t_functions *functions,
						t_cmd_resolution *resolution)
{
	t_expansion	*first_expansion;
	t_string	*cmd_name;
	const char	*name;

	first_expansion = &((t_expansion *)resolution->expansions.data)[0];
	cmd_name = &((t_string *)first_expansion->data)[0];
	name = cmd_name->data;
	resolution->is_declaration_utility = 
		str_cmp(name, "export") == 0
		|| str_cmp(name, "readonly") == 0;
	if (string_get_index_c(cmd_name, '/') >= 0)
		resolution->type = CMD_EXTERNAL;
	else if (cmd_name_is_special_builtin(name, &resolution->builtin))
		resolution->type = CMD_SPECIAL_BUILTIN;
	else if (cmd_name_is_unspecified(name))
		resolution->type = CMD_UNSPECIFIED;
	else if (cmd_name_is_function(functions, name, &resolution->function))
		resolution->type = CMD_FUNCTION;
	else if (cmd_name_is_intrinsic_builtin(name, &resolution->builtin))
		resolution->type = CMD_BUILTIN;
	else if (cmd_name_is_regular_builtin(name, &resolution->builtin))
		resolution->type = CMD_BUILTIN;
	else
		resolution->type = CMD_EXTERNAL;
}

static inline t_error	cmd_expand_word(
							t_functions *functions,
							t_tokens *words,
							size_t index,
							t_cmd_resolution *resolution)
{
	t_token		*word;
	t_exp_flag	flags;
	t_expansion	expansion;
	t_error		err;

	err = tokens_get(words, index, &word);
	if (err.type)
		return (err);
	if (resolution->is_declaration_utility == true
		&& word->assignment_offset >= 0)
		flags = cmd_assignment_expansion_flags();
	else
		flags = cmd_regular_expansion_flags();
	err = expand_token(&expansion, word, flags);
	if (err.type)
		return (err);
	if (expansion.len == 0)
		return (expansion_free(&expansion), err);
	if (!vector_push(&resolution->expansions, &expansion))
		return (expansion_free(&expansion), error_sys());
	if (resolution->expansions.len == 1)
		cmd_compute_name(functions, resolution);
	return (error(ERR_NO));
}

t_error	cmd_resolve(
			t_functions *functions,
			t_tokens *words,
			t_cmd_resolution *out_resolution)
{
	size_t		index;
	t_error		err;

	cmd_resolution_init(out_resolution);
	index = 0;
	err = error(ERR_NO);
	while (index < words->len && err.type == ERR_NO)
	{
		err = cmd_expand_word(functions, words, index, out_resolution);
		index++;
	}
	return (err);
}
