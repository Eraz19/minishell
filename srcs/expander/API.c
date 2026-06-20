/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:29:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 17:35:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "quote_removal_.h"
#include "expander_loader_.h"
#include "field_splitting_.h"
#include "path_name_expansion.h"
#include "expander_substitutions.h"

t_error	expander_word(char ***expansion, t_token token)
{
	char		*word;
	t_expander	state;

	expander_init(&state);
	word = buff_get_string(&token.value);
	if (word == NULL)
		return (expander_free(&state), state.err = error_sys());
	if (expander_load(&state, word, NULL).type)
		return (free(word), expander_free(&state), state.err);
	free(word);
	if (substitutions(&state).type)
		return (expander_free(&state), state.err);
	if (field_splitting(&state).type)
		return (expander_free(&state), state.err);
	if (path_name_expansion(&state).type)
		return (expander_free(&state), state.err);
	if (quote_removal(&state).type)
		return (expander_free(&state), state.err);
	state.err = expander_loader_extract(&state.fields, expansion);
	return (expander_free(&state), state.err);
}

t_error	expander_quote_remove(char **word)
{
	t_error		err;
	t_expander	state;
	char 		**expansion;

	expander_init(&state);
	state.err = expander_load(&state, *word, NULL);
	if (state.err.type)
		return (expander_free(&state), state.err);
	state.err = quote_removal(&state);
	if (state.err.type)
		return (expander_free(&state), state.err);
	err = expander_loader_extract(&state.fields, &expansion);
	if (err.type)
		return (expander_free(&state), err);
	if (expansion[0] == NULL)
	{
		expander_free(&state);
		free(expansion);
		return (free(*word), *word = NULL, error(ERR_NO));
	}
	free(*word);
	*word = expansion[0];
	return (expander_free(&state), free(expansion), error(ERR_NO));
}
