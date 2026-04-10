/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:32:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/19 16:09:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * free_dstr_arr - Frees an array of dynamic string structures
 *
 * @param str_arr The pointer to t_dstr_arr containing the t_dstr, to free
 * @return void
 */
void	free_dstr_arr(t_dstr_arr *str_arr)
{
	size_t	i;

	i = 0;
	if (str_arr->strs == NULL)
		return ;
	while (i < str_arr->len)
		free_dstr(&str_arr->strs[i++]);
	free(str_arr->strs);
	str_arr->strs = NULL;
	str_arr->len = 0;
	str_arr->size = 0;
}

/**
 * free_cstr_arr - Frees an array of constant string structures
 *
 * @param str_arr The pointer to t_cstr_arr containing an t_cstr, to free
 * @return void
 */
void	free_cstr_arr(t_cstr_arr *str_arr)
{
	if (str_arr == NULL)
		return ;
	if (str_arr->strs != NULL)
		free(str_arr->strs);
	str_arr->strs = NULL;
	str_arr->len = 0;
	str_arr->size = 0;
}

/**
 * free_dstr - Frees a dynamic string structure and clears its memory
 *
 * @param str Pointer to the t_dstr to free
 * @return void
 */
void	free_dstr(t_dstr *str)
{
	size_t	i;

	if (str == NULL || str->s == NULL)
		return ;
	i = 0;
	while (i < str->size)
		str->s[i++] = 0;
	free(str->s);
	str->len = 0;
	str->size = 0;
	str->s = NULL;
}
