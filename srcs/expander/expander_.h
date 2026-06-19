/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 13:34:14 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/18 14:42:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER__H
# define EXPANDER__H

# include "expander.h"
# include "expander_field_.h"

typedef struct s_expander
{
	t_error				err;
	t_expander_fields	fields;
}	t_expander;

void	expander_init(t_expander *state);
void	expander_free(t_expander *state);
t_error	expander_load(t_expander *state, char *word, t_context_stack *stack);

#endif
