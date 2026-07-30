#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "scanner.h"
#include "scanner_priv.h"

t_error    env_get_alias(const t_string *name, const t_string **out_value, bool add_to_stack);

static bool	ends_in_blank(const t_lexer_input_stack_item *alias_exp)
{
	if (alias_exp == NULL || alias_exp->str.len == 0)
		return (false);
	return (is_blank(alias_exp->str.data[alias_exp->str.len - 1]));
}

static bool	is_word_containing_quoting(char *word)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\''
			|| is_context_squote_start(word + i)
			|| is_context_dquote_start(word + i)
			|| is_context_dollar_squote_start(word + i))
			return (true);
		i++;
	}
	return (false);
}

t_error	find_alias_value(t_scanner *scanner, const t_string **out, t_token *src)
{
	bool						expandable;
	bool						position_exempt;
	t_lexer_input_stack_item	*current_input;

	current_input = scanner->lexer.input;
	position_exempt = current_input->alias_position_exempt;
	current_input->alias_position_exempt = false;
	expandable = !is_word_containing_quoting(src->value.data);
	if (expandable && !position_exempt)
	{
		scanner->err = parser_can_next_token_be_a_cmd_name_or_word(scanner->parser, &expandable);
		if (scanner->err.type)
			return (scanner->err);
	}
	if (!expandable)
		return (*out = NULL, scanner->err = error(ERR_NO));
	scanner->err = env_get_alias(&src->value, out, true);
	if (scanner->err.type)
		return (scanner->err);
	return (token_free(src), scanner->err);
}

t_error	expand_alias(t_scanner *scanner, t_token *out)
{
	t_lexer_input_stack_item	alias_exp;
	const t_string				*alias_value;
	t_lexer_input_stack_item	*current_input;

	current_input = scanner->lexer.input;
	lexer_input_stack_item_init(&alias_exp);
	if (find_alias_value(scanner, &alias_value, out).type)
	{
		if (scanner->err.type == ERR_VAR_NOT_FOUND)
			return (scanner->err = error(ERR_NO));
		return (scanner->err = requalify_scanner_error(scanner->err));
	}
	if (alias_value == NULL)
		return (scanner->err = error(ERR_NO));
	if (!string_dup(&alias_exp.str, alias_value))
		return (requalify_scanner_error(scanner->err = error_sys()));
	current_input->alias_position_exempt = ends_in_blank(&alias_exp);
	if (lexer_push_alias(&scanner->lexer, &alias_exp).type)
		string_free(&alias_exp.str);
	return (scanner->err = requalify_scanner_error(scanner->lexer.err));
}
