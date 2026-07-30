#include "path_comps_.h"

bool	path_comps_have_special(const t_path_comps *comps)
{
	size_t		i;
	t_path_comp	*comp;

	i = 0;
	while (i < comps->len)
	{
		comp = &((t_path_comp *)comps->data)[i++];
		if (comp->special)
			return (true);
	}
	return (false);
}

t_error	path_comps_get(t_path_comp *out, const t_path_comps *src, size_t i)
{
	if (src->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (i >= src->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*out = ((t_path_comp *)src->data)[i];
	return (error(ERR_NO));
}
