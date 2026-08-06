/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_cmd_assignment_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:18 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:59:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_assign_priv.h"
#include <assert.h>	// DEBUG

#define CITATION	"POSIX 2.9.1.1: Each variable assignment shall be expanded \
for [...] but no field splitting -> POSIX 2.6: [...] shall\
 expand to a single field"

t_error	cmd_assignment_expand(
			t_token *token,
			t_exp_flag flags,
			t_string *out,
			int *exit_status)
{
	t_expansion	expansion;
	t_error		err;

	err = expand_token(&expansion, token, exit_status, flags);
	if (err.type)
		return (err);
	if (expansion.len != 1)
		return (expansion_merge(token->value.data, CITATION, &expansion, out));
	expansion_take(&expansion, 0, out);
	expansion_free(&expansion);
	assert(token->assignment_offset >= 0);
	assert((size_t)token->assignment_offset < out->len);
	assert(out->data[token->assignment_offset] == '=');
	return (err);
}
