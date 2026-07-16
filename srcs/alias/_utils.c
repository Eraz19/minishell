#include "alias_.h"
#include "builder.h"
#include "context.h"
#include "alias_stack_.h"

static bool	is_word_containing_quoting(char *word)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'' ||
			is_context_squote_start(word + i) ||
			is_context_dquote_start(word + i) ||
			is_context_dollar_squote_start(word + i))
			return (true);
		i++;
	}
	return (false);
}

bool	alias_is_valid_name(const char *name)
{
	size_t	i;

	if (name == NULL || *name == '\0')
		return (false);
	i = 0;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) &&
			name[i] != '_' &&
			name[i] != '!' &&
			name[i] != '%' &&
			name[i] != ',' &&
			name[i] != '-' &&
			name[i] != '@')
			return (false);
		i++;
	}
	return (true);
}

bool	is_token_alias_expandable(t_alias *alias, char *word)
{
	bool	can_next_token_be_a_cmd_name;

	alias->err = error(ERR_NO);
	if (is_word_containing_quoting(word))
		return (false);
	else if (!alias_is_valid_name(word))
		return (false);
	else if (!hashmap_contains(&alias->map, word))
		return (false);
	else if (alias_stack_contains(&alias->stack, word))
		return (false);
	else if (!alias->disable_position)
	{
		can_next_token_be_a_cmd_name = false;
		alias->err = builder_can_next_word_be_a_cmd_name(
				alias->parser,
				&can_next_token_be_a_cmd_name);
		if (alias->err.type || !can_next_token_be_a_cmd_name)
			return (false);
	}
	return (true);
}

void	set_position_for_next_word(t_alias *alias, t_string *expansion)
{
	alias->disable_position = expansion != NULL
		&& expansion->len > 0
		&& is_blank(expansion->data[expansion->len - 1]);
}
