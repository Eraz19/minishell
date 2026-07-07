#include <sys/stat.h>
#include "globbing_.h"
#include "path_matches_.h"

t_error	emit_path_matches(t_expander *expander, t_path_matches *matches)
{
	size_t			i;
	t_word_item_opt	opt;
	t_error			err;
	t_word			word;
	t_string		*match;

	i = 0;
	path_matches_sort(matches);
	opt = (t_word_item_opt){0};
	opt.is_expand_res = true;
	while (i < matches->len)
	{
		err = path_matches_get(&match, matches, i);
		if (err.type)
			return (err);
		expander->err = from_str(&word, match, opt);
		if (expander->err.type)
			return (expander->err);
		expander->err = fields_push(&expander->fields_exp, word);
		if (expander->err.type)
			return (word_free(&word), expander->err);
		i++;
	}
	return (expander->err);
}

t_error	filter_existing_file(t_path_matches *matches)
{
	size_t			i;
	t_error			err;
	t_string		*match;
	struct stat		file_stat;
	t_path_matches	kept_paths;

	i = 0;
	path_matches_init(&kept_paths);
	while (i < matches->len)
	{
		err = path_matches_get(&match, matches, i);
		if (err.type)
			return (vector_free(&kept_paths, NULL), err);
		if (lstat(match->data, &file_stat) == 0)
		{
			err = path_matches_push(&kept_paths, match);
			if (err.type)
				return (vector_free(&kept_paths, NULL), error_sys());
		}
		else
			string_free(match);
		i++;
	}
	return (vector_free(matches, NULL), *matches = kept_paths, error(ERR_NO));
}

t_error	find_path_comp_matches(
			t_path_matches *out,
			const t_path_comps *comps,
			t_string *seed,
			size_t i)
{
	t_error		err;
	t_path_comp	comp;

	err = path_comps_get(&comp, comps, i);
	if (err.type)
		return (string_free(seed), err);
	if (comp.special)
		err = add_path_comp_lookup(out, &comp, i == 0);
	else
		err = add_path_comp(out, &comp, i == 0);
	if (err.type)
		return (string_free(seed), err);
	return (error(ERR_NO));
}

t_error	find_path_comps_matches(t_path_matches *out, const t_path_comps *comps)
{
	size_t			i;
	t_error			err;
	t_string		seed;
	t_path_comp		last_comp;

	path_matches_init(out);
	string_init(&seed, 0, NULL, 0);
	err = path_matches_push(out, &seed);
	if (err.type)
		return (string_free(&seed), err);
	i = 0;
	while (i < comps->len && out->len > 0)
	{
		err = find_path_comp_matches(out, comps, &seed, i);
		if (err.type)
			return (string_free(&seed), path_matches_free(out), err);
		i++;
	}
	err = path_comps_get(&last_comp, comps, comps->len - 1);
	if (!err.type && out->len > 0 && !last_comp.special)
		err = filter_existing_file(out);
	if (err.type)
		return (vector_free(out, string_free_void), err);
	return (error(ERR_NO));
}

t_error	path_globbing(t_expander *expander, t_path_comps *src, bool *globbed)
{
	t_path_matches	matches;

	*globbed = false;
	if (!path_comps_have_special(src))
		return (path_comps_free(src), expander->err);
	expander->err = find_path_comps_matches(&matches, src);
	if (expander->err.type)
		return (path_comps_free(src), expander->err);
	if (matches.len > 0)
	{
		expander->err = emit_path_matches(expander, &matches);
		*globbed = (expander->err.type == ERR_NO);
	}
	path_comps_free(src);
	return (vector_free(&matches, string_free_void), expander->err);
}
