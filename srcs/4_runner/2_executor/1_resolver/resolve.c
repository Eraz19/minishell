#include "cmd_resolver.h"
#include "cmd_resolver_priv.h"
#include "tokens.h"
#include "expander.h"
#include "cmd_expansion.h"

static inline void	cmd_compute_name(t_cmd *cmd, const t_functions *functions)
{
	cmd->is_declaration_utility = 
		str_cmp(cmd->name.data, "export") == 0
		|| str_cmp(cmd->name.data, "readonly") == 0;
	if (string_get_index_c(&cmd->name, '/') >= 0)
		cmd->type = CMD_EXTERNAL;
	else if (cmd_name_is_special_builtin(cmd->name.data, &cmd->builtin))
		cmd->type = CMD_SPECIAL_BUILTIN;
	else if (cmd_name_is_unspecified(cmd->name.data))
		cmd->type = CMD_UNSPECIFIED;
	else if (cmd_name_is_function(functions, cmd->name.data, &cmd->function))
		cmd->type = CMD_FUNCTION;
	else if (cmd_name_is_intrinsic_builtin(cmd->name.data, &cmd->builtin))
		cmd->type = CMD_BUILTIN;
	else if (cmd_name_is_regular_builtin(cmd->name.data, &cmd->builtin))
		cmd->type = CMD_BUILTIN;
	else
		cmd->type = CMD_EXTERNAL;
}

// @ret ERR_LIBC
# include <stdio.h>
# include "params.h"
static inline t_error	cmd_add_to_argv(
							t_cmd *cmd,
							const t_functions *functions,
							const t_expansion *expansion)
{
	t_string	*expanded_word;
	size_t		i;

	fprintf(stderr, "[%s()] expansion.len = %zu\n", __func__, expansion->len);
	i = 0;
	while (i < expansion->len)
	{
		expanded_word = &((t_string *)expansion->data)[i];
		t_string ifs_value;
		t_error err = params_get_from_const("IFS", &ifs_value);
		if (err.type == ERR_NO)
			fprintf(stderr, "[%s()] IFS = '%s'\n", __func__, ifs_value.data);
		else
			fprintf(stderr, "[%s()] error = '%s'\n", __func__, error_to_string(err));
		fprintf(stderr, "[%s()] expansion.word[%zu] = '%s'\n", __func__, i, expanded_word->data);
		if (!vector_push(&cmd->argv, &expanded_word->data))
			return (error_sys());
		expanded_word->cap = 0;
		i++;
	}
	if (expansion->len > 0 && cmd->type == CMD_NONE)
	{
		expanded_word = &((t_string *)expansion->data)[0];
		cmd->name.data = expanded_word->data;
		cmd->name.len = expanded_word->len;
		cmd_compute_name(cmd, functions);
	}
	return (error(ERR_NO));
}

// @ret TODO
static inline t_error	cmd_expand_word(
							t_cmd *cmd,
							const t_functions *functions,
							const t_tokens *words,
							size_t index)
{
	t_token		*word;
	t_exp_flag	flags;
	t_expansion	expansion;
	t_error		err;

	err = tokens_get(words, index, &word);
	if (err.type)
		return (err);
	if (cmd->is_declaration_utility == true
		&& word->assignment_offset >= 0)
		flags = cmd_assignment_expansion_flags();
	else
		flags = cmd_regular_expansion_flags();
	err = expand_token(&expansion, word, flags);
	if (err.type)
		return (err);
	err = cmd_add_to_argv(cmd, functions, &expansion);
	expansion_free(&expansion);
	return (err);
}

t_error	cmd_resolve(
			t_cmd *cmd,
			const t_functions *functions,
			const t_tokens *words)
{
	size_t	index;
	char	*null;
	t_error	err;

	index = 0;
	err = error(ERR_NO);
	while (index < words->len && err.type == ERR_NO)
	{
		err = cmd_expand_word(cmd, functions, words, index);
		index++;
	}
	if (err.type == ERR_NO)
	{
		null = NULL;
		if (!vector_push(&cmd->argv, &null))
			return (error_sys());
	}
	return (err);
}
