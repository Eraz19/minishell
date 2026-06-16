/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:41:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 15:41:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIELD_SPLITTING_H
# define FIELD_SPLITTING_H

# include "error.h"
# include "libft.h"

typedef struct s_field_splitting
{
	size_t	i;
	t_error	err;
	char	*word;
	bool	reached_EOW;
}	t_field_splitting;

#endif
