/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unwrap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:40:14 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/29 16:45:29 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/***
 * dstr_arr_unwrap - Unwraps a dynamic string array into a NULL-terminated
 * 						array of C-strings
 *
 * @param arr The t_dstr_arr to unwrap
 * @return A NULL-terminated array of C-strings (t_i8 **)
 *
 * @error: If allocation fails, returns NULL (errno ENOMEM).
 */
t_i8	**dstr_arr_unwrap(t_dstr_arr arr)
{
	size_t	i;
	t_i8	**res;

	res = malloc(sizeof(t_i8 *) * (arr.len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < arr.len)
		1 && (res[i] = arr.strs[i].s, ++i);
	res[i] = NULL;
	return (res);
}

/***
 * cstr_arr_unwrap - Unwraps a constant string array into a NULL-terminated
 * 						array of C-strings
 *
 * @param arr The t_cstr_arr to unwrap
 * @return A NULL-terminated array of C-strings (const t_i8 **)
 *
 * @error: If allocation fails, returns NULL (errno ENOMEM).
 */
const t_i8	**cstr_arr_unwrap(t_cstr_arr arr)
{
	size_t		i;
	const t_i8	**res;

	res = malloc(sizeof(t_i8 *) * (arr.len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < arr.len)
		1 && (res[i] = arr.strs[i].s, ++i);
	res[i] = NULL;
	return (res);
}
