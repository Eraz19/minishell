/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 16:59:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/06 17:03:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__quote_remove_context.h"

t_error	quote_remove_rules(t_quote_remove *state)
{
	if (is_context_squote_start(state->input + state->i)) 
		return (context_squote(state));
	else if (is_context_dquote_start(state->input + state->i))
		return (context_dquote(state));
	else if (is_context_dollar_squote_start(state->input + state->i))
		return (context_dollar_squote(state));
	else
		return (context_none(state));
}
