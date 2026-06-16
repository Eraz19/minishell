/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 16:59:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:46:05 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "quote_remove_context_.h"

t_error	quote_remove_rules(t_quote_remove *state)
{
	if (is_context_squote_start(state->input + state->i)) 
		return (expander_context_squote(state));
	else if (is_context_dquote_start(state->input + state->i))
		return (expander_context_dquote(state));
	else if (is_context_dollar_squote_start(state->input + state->i))
		return (expander_context_dollar_squote(state));
	else
		return (expander_context_none(state));
}
