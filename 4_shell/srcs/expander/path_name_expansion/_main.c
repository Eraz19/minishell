/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:45:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "globbing_.h"
#include "path_comps_.h"
#include "quote_removal_.h"

static t_error	prepare_path_name_word(t_expander *expander, t_word *original)
{
	expander->err = word_dup(original, &expander->word);
	if (expander->err.type)
		return (expander->err);
	word_init(&expander->word_exp);
	while (expander->word.len > 0)
	{
		if (quote_remove_char(expander).type)
		{
			word_free(&expander->word_exp);
			return (word_free(&expander->word), expander->err);
		}
	}
	return (word_free(&expander->word), expander->err);
}

static t_error	release_path_word(
					t_error err,
					t_path_comps *comps,
					t_word *original)
{
	return (path_comps_free(comps), word_free(original), err);
}

static t_error	path_name_expansion_word(t_expander *expander)
{
	bool			globbed;
	t_word			original;
	t_path_comps	path_comps;

	globbed = false;
	expander->err = fields_fpop(&expander->word, &expander->fields);
	if (expander->err.type)
		return (expander->err);
	if (prepare_path_name_word(expander, &original).type)
		return (word_free(&original), expander->err);
	expander->err = path_comps_load(&path_comps, &expander->word_exp);
	word_free(&expander->word_exp);
	if (expander->err.type)
		return (word_free(&original), expander->err);
	expander->err = path_globbing(expander, &path_comps, &globbed);
	if (expander->err.type || globbed)
		return (release_path_word(expander->err, &path_comps, &original));
	expander->err = fields_push(&expander->fields_exp, original);
	if (expander->err.type)
		return (release_path_word(expander->err, &path_comps, &original));
	return (expander->err);
}

t_error	path_name_expansion(t_expander *expander)
{
	bool	is_noglob;

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
