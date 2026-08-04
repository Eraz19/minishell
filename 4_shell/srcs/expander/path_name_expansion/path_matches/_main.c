/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:45:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_matches_.h"

t_error	path_matches_push(t_path_matches *matches, t_string *match)
{
	if (!vector_push(matches, match))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	path_matches_get(t_string **out, t_path_matches *matches, size_t i)
{
	if (matches->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (i >= matches->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*out = &((t_string *)matches->data)[i];
	return (error(ERR_NO));
}

t_error	add_path_comp(t_path_matches *out, t_path_comp *src, bool first)
{
	size_t		i;
	t_error		err;
	t_string	*match;

	i = 0;
	while (i < out->len)
	{
		err = path_matches_get(&match, out, i);
		if (err.type)
			return (err);
		if (!first && !string_append_n(match, "/", 1))
			return (error_sys());
		err = path_match_append(match, src->pattern.data);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

t_error	add_path_comp_lookup(t_path_matches *out, t_path_comp *src, bool first)
{
	size_t			i;
	t_error			err;
	t_string		*match;
	t_path_matches	new_matches;

	i = 0;
	path_matches_init(&new_matches);
	while (i < out->len)
	{
		err = path_matches_get(&match, out, i);
		if (err.type)
			return (vector_free(&new_matches, string_free_void), err);
		err = add_lookup_dir_matching(&new_matches, match, src, first);
		if (err.type)
			return (vector_free(&new_matches, string_free_void), err);
		i++;
	}
	vector_free(out, string_free_void);
	*out = new_matches;
	return (error(ERR_NO));
}

void	path_matches_sort(t_path_matches *matches)
{
	size_t		i;
	size_t		j;
	t_string	tmp_match;
	t_string	*match_arr;

	i = 1;
	match_arr = (t_string *)matches->data;
	while (i < matches->len)
	{
		j = i;
		while (j > 0 && str_cmp(match_arr[j - 1].data, match_arr[j].data) > 0)
		{
			tmp_match = match_arr[j - 1];
			match_arr[j - 1] = match_arr[j];
			match_arr[j] = tmp_match;
			j--;
		}
		i++;
	}
}
