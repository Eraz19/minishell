#include "context.h"
#include "param_braced_.h"

static bool	pattern_char_active(t_word_item item)
{
	if (item.opt.escaped)
		return (false);
	if (is_context_quoting(item.opt.local_quoted)
		|| item.opt.local_quoted == CONTEXT_HEREDOC)
		return (false);
	return (true);
}

static bool	pattern_push_item(t_string *out, t_word_item item)
{
	char	c;
	char	backslash;

	c = item.c;
	backslash = '\\';
	if (pattern_char_active(item) && (c == '*' || c == '?' || c == '['))
		return (string_append_n(out, &c, 1));
	if (c == '*' || c == '?' || c == '[' || c == '\\')
		if (!string_append_n(out, &backslash, 1))
			return (false);
	return (string_append_n(out, &c, 1));
}

t_error	braced_build_pattern(
			t_expander *expander,
			t_word *operand,
			t_string *out)
{
	size_t		i;
	t_word		expanded;
	t_word_item	item;

	expander->err = expand_operand(expander, operand, &expanded);
	if (expander->err.type)
		return (word_free(&expanded), expander->err);
	if (!string_init(out, 0, "", -1))
		return (word_free(&expanded), expander->err = error_sys());
	i = 0;
	while (i < expanded.len)
	{
		expander->err = word_get(&item, &expanded, i++);
		if (expander->err.type)
			return (word_free(&expanded), string_free(out), expander->err);
		if (!pattern_push_item(out, item))
			return (word_free(&expanded), string_free(out),
				expander->err = error_sys());
	}
	return (word_free(&expanded), expander->err);
}
