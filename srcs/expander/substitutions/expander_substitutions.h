/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_substitutions.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:38:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 10:46:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_SUBSTITUTIONS_H
# define EXPANDER_SUBSTITUTIONS_H

# include "error.h"
# include "expander_.h"

typedef struct s_expander_substitutions
{
	size_t	i;
	t_error	err;
	char	*word;
	bool	reached_EOW;
}	t_expander_substitutions;

t_error	substitutions(t_expander *state);

#endif
