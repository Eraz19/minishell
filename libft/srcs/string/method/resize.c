/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:34:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 19:46:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * str_cshift - Shifts a t_cstr constant string by a given offset
 *
 * @param str The t_cstr to shift
 * @param offset The number of characters to shift the string pointer forward
 * @return The shifted t_cstr with updated pointer, len, and size
 *
 * @args: If str.s is NULL, returns a NULL t_cstr.
 *        If offset > str.len, returns a NULL t_cstr (beyond bounds).
 *        If offset == str.len, returns an empty string.
 */
t_cstr	str_cshift(t_cstr str, size_t offset)
{
	if (str.s == NULL)
		return (str);
	if (offset > str.len)
		return (cstr(NULL));
	str.s += offset;
	str.len -= offset;
	str.size -= offset;
	return (str);
}

/**
 * str_dshift - Shifts a t_dstr constant string by a given offset
 *
 * @param str The t_dstr to shift
 * @param offset The number of characters to shift the string pointer forward
 * @return The shifted t_dstr as a t_cstr with updated pointer, len, and size
 *
 * @args: If str.s is NULL, returns a NULL t_cstr.
 *        If offset > str.len, returns a NULL t_cstr (beyond bounds).
 *        If offset == str.len, returns an empty string.
 */
t_cstr	str_dshift(t_dstr str, size_t offset)
{
	t_cstr	res;

	if (str.s == NULL)
		return (cstr(NULL));
	if (offset > str.len)
		return (cstr(NULL));
	res = cstr_d(str);
	res.s += offset;
	res.len -= offset;
	res.size -= offset;
	return (res);
}

/**
 * str_cshrink - Shrinks a t_cstr constant string by a given offset
 *
 * @param str The t_cstr to shrink
 * @param offset The number of characters to reduce from the end
 * @return The shrunk t_cstr with updated len and size
 *
 * @args: If str.s is NULL, returns a NULL t_cstr.
 *        If offset > str.len, returns a NULL t_cstr (beyond bounds).
 *        If offset == str.len, returns an empty string.
 */
t_cstr	str_cshrink(t_cstr str, size_t offset)
{
	if (str.s == NULL)
		return (str);
	if (offset > str.len)
		return (cstr(NULL));
	str.len -= offset;
	str.size -= offset;
	return (str);
}

/**
 * str_dshrink - Shrinks a t_dstr constant string by a given offset
 *
 * @param str The t_dstr to shrink
 * @param offset The number of characters to reduce from the end
 * @return The shrunk t_dstr as a t_cstr with updated len and size
 *
 * @args: If str.s is NULL, returns a NULL t_cstr.
 *        If offset > str.len, returns a NULL t_cstr (beyond bounds).
 *        If offset == str.len, returns an empty string.
 */
t_cstr	str_dshrink(t_dstr str, size_t offset)
{
	t_cstr	res;

	if (str.s == NULL)
		return (cstr(NULL));
	if (offset > str.len)
		return (cstr(NULL));
	res = cstr_d(str);
	res.len -= offset;
	res.size -= offset;
	return (res);
}
