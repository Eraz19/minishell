/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:20:20 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:21:25 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirector_priv.h"
#include "expander.h"

#define CITATION		"POSIX 2.10.2: The expansions specified in 2.7 \
Redirection shall occur. As specified there, exactly \
one field can result (or the result is unspecified)"

// @ret ERR_POSIX_EXPANSION / ERR_REDIRECTION / ERR_INTERNAL / ERR_LIBC
static inline t_error	redirect_expand_word(
							t_token *token,
							t_string *out,
							int *exit_status)
{
	t_exp_flag	flags;
	t_expansion	expansion;
	t_error		err;

	flags = expansion_flags_redirection();
	err = expand_token(&expansion, token, exit_status, flags);
	if (err.type)
		return (err);
	else if (expansion.len != 1)
		return (expansion_merge(token->value.data, CITATION, &expansion, out));
	expansion_take(&expansion, 0, out);
	expansion_free(&expansion);
	return (error(ERR_NO));
}

t_error	redirect_expand(t_redir *redir, int *exit_status)
{
	t_exp_flag	flags;
	t_error		err;

	if (redir->operation == AST_REDIR_HEREDOC)
	{
		flags = expansion_flags_heredoc_body();
		if (redir->expand_heredoc_body)
			return (expand_str_merged(&redir->expanded_word,
					redir->heredoc_body, exit_status, flags));
		else if (!string_dup(&redir->expanded_word, redir->heredoc_body))
			return (error_sys());
	}
	else
		err = redirect_expand_word(&redir->word, &redir->expanded_word,
				exit_status);
	if (err.type == ERR_NO && redir->is_location)
		err = redirect_expand_word(&redir->location, &redir->expanded_location,
				exit_status);
	return (err);
}
