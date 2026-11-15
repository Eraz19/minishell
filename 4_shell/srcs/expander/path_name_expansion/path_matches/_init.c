/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:45:25 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_matches_.h"

void	path_matches_init(t_path_matches *matches)
{
	vector_init(matches, sizeof(t_string), 0);
}

void	path_matches_free(t_path_matches *matches)
{
	vector_free(matches, string_free_void);
}
