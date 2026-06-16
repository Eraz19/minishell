/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:58:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 23:47:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_REMOVE__H
# define QUOTE_REMOVE__H

# include "libft.h"
# include "error.h"
# include "expander.h"

typedef struct s_quote_remove
{
	size_t	i;
	t_error	err;
	char	*word;
	bool	reached_EOW;
	t_buff	expanded_word;
}	t_quote_remove;

void	quote_remove_init(t_quote_remove *state);
t_error	quote_remove_free(t_quote_remove *state);
t_error	quote_remove_load(t_quote_remove *state, t_buff *word);

t_error	quote_remove_keep(t_quote_remove *state);
t_error	quote_remove_consume(t_quote_remove *state);
void	quote_remove_advance(t_quote_remove *state, size_t offset);

t_error	quote_removal(t_expansion *expansion);

#endif
