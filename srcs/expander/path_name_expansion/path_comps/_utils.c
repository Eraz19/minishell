#include "utils.h"
#include "path_comps_.h"

bool	path_comp_is_special(const char *pattern)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (pattern[i] != '\0')
	{
		if (pattern[i] == '\\' && pattern[i + 1] != '\0')
			i += 2;
		else if (pattern[i] == '*' || pattern[i] == '?')
			return (true);
		else if (pattern[i] == '[')
		{
			len = 0;
			if (valid_bracket_exp_len(pattern + i + 1, &len))
				return (true);
			i++;
		}
		else
			i++;
	}
	return (false);
}

t_error	path_comp_push(t_path_comp *comp, t_word_item item)
{
	bool	quotes;

	quotes = (item.opt.quoted != CONTEXT_NONE || item.opt.escaped);
	if (quotes && str_chr("*?[]!^-\\", item.c) != NULL)
	{
		if (!string_append_n(&comp->pattern, "\\", 1))
			return (error_sys());
	}
	if (!string_append_n(&comp->pattern, &item.c, 1))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	path_comp_emit(t_path_comps *comps, t_path_comp *comp)
{
	t_error	err;

	comp->special = path_comp_is_special(comp->pattern.data);
	err = path_comps_push(comps, *comp);
	if (err.type)
		return (err);
	return (path_comp_init(comp), error(ERR_NO));
}

t_error	path_comps_push(t_path_comps *comps, t_path_comp comp)
{
	if (!vector_push(comps, &comp))
		return (error_sys());
	return (error(ERR_NO));
}
