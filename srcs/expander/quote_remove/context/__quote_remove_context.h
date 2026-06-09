/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __quote_remove_context.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:27:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:55:28 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __QUOTE_REMOVE_CONTEXT_H
# define __QUOTE_REMOVE_CONTEXT_H

# include "__quote_remove.h"

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
