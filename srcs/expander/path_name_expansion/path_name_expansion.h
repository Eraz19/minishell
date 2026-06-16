/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_name_expansion.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:42:10 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 15:42:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_NAME_EXPANSION_H
# define PATH_NAME_EXPANSION_H

# include "error.h"
# include "libft.h"

typedef struct s_path_name_expansion
{
	size_t	i;
	t_error	err;
	char	*word;
	bool	reached_EOW;
}	t_path_name_expansion;

#endif
