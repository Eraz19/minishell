#include "expansion_.h"

void	expansion_init(t_expansion *expansion)
{
	*expansion = (t_expansion){0};
	vector_init(expansion, sizeof(t_string), 0);
}

void	expansion_free(t_expansion *expansion)
{
	vector_free(expansion, string_free_void);
	*expansion = (t_expansion){0};
}

void	expansion_free_void(void *expansion)
{
	expansion_free(expansion);
}

t_error	expansion_load(t_expansion *out, t_fields *src)
{
	t_error		err;
	t_string	str;
	t_word		word;

	expansion_init(out);
	while (src->len > 0)
	{
		err = fields_fpop(&word, src);
		if (err.type)
			return (expansion_free(out), err);
		err = to_str(&str, &word, 0, word.len);
		if (err.type)
			return (expansion_free(out), err);
		err = expansion_push(out, &str);
		if (err.type)
			return (string_free(&str), expansion_free(out), err);
	}
	return (error(ERR_NO));
}

