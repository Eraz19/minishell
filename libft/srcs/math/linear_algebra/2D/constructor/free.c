/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:08:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:37:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * free_vec2_arr - Frees an array of 2D vector structures
 *
 * @param vec_arr The pointer to t_vec2_arr containing the t_vec2, to free
 * @return void
 */
void	free_vec2_arr(t_vec2_arr *vec_arr)
{
	size_t	i;

	if (vec_arr == NULL || vec_arr->vecs == NULL)
		return ;
	i = 0;
	while (i < vec_arr->size)
		vec_arr->vecs[i++].vec_u = vec2_u32(0, 0);
	free(vec_arr->vecs);
	vec_arr->vecs = NULL;
	vec_arr->len = 0;
	vec_arr->size = 0;
}
