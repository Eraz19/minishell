/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove_context_.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:27:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:46:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_REMOVE_CONTEXT__H
# define QUOTE_REMOVE_CONTEXT__H

# include "quote_remove_.h"

typedef struct s_context_args
{
	bool	(*is_end)(char, void *);
	bool	(*is_in_whitelist)(char);
}	t_context_args;

t_error	expander_context_scan(t_quote_remove *state, t_context_args args);
t_error	expander_context_escape(t_quote_remove *state, t_context_args args);

t_error	expander_context_none(t_quote_remove *state);
t_error	expander_context_squote(t_quote_remove *state);
t_error	expander_context_dquote(t_quote_remove *state);
t_error	expander_context_dollar_squote(t_quote_remove *state);

#endif
