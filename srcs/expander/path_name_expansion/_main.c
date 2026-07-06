#include "options.h"
#include "path_name_expansion_.h"

bool string_split_on_char(t_string *src, char c, t_vector *out);

bool	is_globbing(t_string *path_comp)
{
	bool	is_quoted;
	size_t	i;

	if (path_comp->len == 0)
		return (false);
	i = 0;
	while (i < path_comp->len)
	{
		if (path_comp->str[i] == '*' || path_comp->str[i] == '?')
			return (true);
		i++;
	}
}

t_error path_name_expansion_comps(t_expander *expander, t_fields *path_comps)
{
	size_t		i;
	t_string	path_comp;
	t_word		path_word;
	t_vector	matching_paths;

	i = 0;
	fields_init(&matching_paths);
	while (i < path_comps->len)
	{
		if (!vector_remove(path_comps, i, &path_comp))
		{
			expander->err = error_sys();
			return (string_free(&path_comp), expander->err);
		}
		if (is_globbing(&path_comp))
		{

		}
		else
		{

		}
		i++;
	}
}

t_error	path_name_expansion_word(t_expander *expander)
{
	t_fields	path_comps;

	expander->err = fields_fpop(&expander->word, &expander->fields);
	if (expander->err.type)
		return (expander->err);
	expander->err = word_split(&path_comps, &expander->word, '/');
	if (expander->err.type)
		return (expander->err);
	path_name_expansion_comps(expander, &path_comps);
	return (word_free(&expander->word), expander->err);
}

t_error	path_name_expansion(t_expander *expander)
{
	bool is_noglob;

	expander->err = option_is_active(OPT_NOGLOB, &is_noglob);
	if (expander->err.type || is_noglob)
		return (expander->err);
	fields_init(&expander->fields_exp);
	while (expander->fields.len > 0)
	{
		if (path_name_expansion_word(expander).type)
			return (fields_free(&expander->fields_exp), expander->err);
	}
	fields_free(&expander->fields);
	expander->fields = expander->fields_exp;
	fields_init(&expander->fields_exp);
	return (expander->err);
}
