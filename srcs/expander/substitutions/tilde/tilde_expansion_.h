/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion_.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:59:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 14:42:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILDE_EXPANSION__H
# define TILDE_EXPANSION__H

#include "expander_.h"

typedef struct s_tilde_expansion
{
	char	*home;
}	t_tilde_expansion;

bool	is_tilde_expansion(t_expander *state, t_expander_word *word);


#endif
