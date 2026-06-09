/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __quote_remove.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:58:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/07 11:18:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __QUOTE_REMOVE_H
# define __QUOTE_REMOVE_H

# include "libft.h"
# include "error.h"
# include "context.h"

typedef struct s_quote_remove
{
	size_t			i;
	t_error			err;
	t_buff			res;
	char			*input;
	bool			reached_EOW;
}	t_quote_remove;

void	quote_remove_init(t_quote_remove *state);
t_error	quote_remove_free(t_quote_remove *state);
t_error	quote_remove_load(t_quote_remove *state, t_buff *input);

t_error	quote_remove_keep(t_quote_remove *state);
t_error	quote_remove_consume(t_quote_remove *state);
void	quote_remove_advance(t_quote_remove *state, size_t offset);

#endif
