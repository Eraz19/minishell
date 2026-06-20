/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_name_expansion.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:42:10 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 17:12:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_NAME_EXPANSION_H
# define PATH_NAME_EXPANSION_H

# include "expander_.h"

typedef struct s_path_name_expansion
{
	size_t	i;
	t_error	err;
	char	*word;
	bool	reached_EOW;
}	t_path_name_expansion;

t_error	path_name_expansion(t_expander *state);

#endif
