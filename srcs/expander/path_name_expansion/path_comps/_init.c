#include "word_.h"
#include "path_comps_.h"

void	path_comps_init(t_path_comps *comps)
{
	vector_init(comps, sizeof(t_path_comp), 0);
}

void	path_comps_free(t_path_comps *comps)
{
	vector_free(comps, (void (*)(void *))path_comp_free);
}

# include <stdio.h>
t_error	path_comps_load(t_path_comps *comps, const t_word *src)
{
	size_t		i;
	t_error		err;
	t_word_item	item;
	t_path_comp	glob_comp;

	i = 0;
	path_comp_init(&glob_comp);
	fprintf(stderr, "[%s()] before loop\n", __func__);
	while (i < src->len)
	{
		fprintf(stderr, "[%s()] before word_get\n", __func__);
		err = word_get(&item, src, i);
		if (err.type)
			return (path_comp_free(&glob_comp), path_comps_free(comps), err);
		fprintf(stderr, "[%s()] after word_get\n", __func__);
		if (item.c == '/')
			err = path_comp_emit(comps, &glob_comp);
		else
			err = path_comp_push(&glob_comp, item);
		fprintf(stderr, "[%s()] after emit/push\n", __func__);
		if (err.type)
			return (path_comp_free(&glob_comp), path_comps_free(comps), err);
		fprintf(stderr, "[%s()] after emit/push error\n", __func__);
		i++;
	}
	fprintf(stderr, "[%s()] after loop\n", __func__);
	err = path_comps_push(comps, glob_comp);
	if (err.type)
		return (path_comp_free(&glob_comp), path_comps_free(comps), err);
	fprintf(stderr, "[%s()] after path_comps_push()\n", __func__);
	return (error(ERR_NO));
}

void	path_comp_init(t_path_comp *comp)
{
	comp->special = false;
	string_init(&comp->pattern, 0, NULL, 0);
}

void	path_comp_free(t_path_comp *comp)
{
	string_free(&comp->pattern);
	*comp = (t_path_comp){0};
}
