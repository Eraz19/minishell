/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:32:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/28 11:34:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tuple.h"
#include "libft_types.h"

/**
 * tuple2_ - Creates a tuple structure with two elements
 *
 * @param first The first element of the tuple
 * @param second The second element of the tuple
 * @return A t_tuple2 structure containing the two elements
 */
t_tuple2	tuple2_(t_u32 first, t_u32 second)
{
	t_tuple2	res;

	res.first = first;
	res.second = second;
	return (res);
}

/**
 * tuple3_t - Creates a tuple structure with three elements
 *
 * @param tuple The tuple to copy
 * @return A t_tuple3 structure containing the three elements
 */
t_tuple3	tuple3_t(t_tuple3 tuple)
{
	t_tuple3	res;

	res.first = tuple.first;
	res.second = tuple.second;
	res.third = tuple.third;
	return (res);
}

/**
 * tuple3_ - Creates a tuple structure with three elements
 *
 * @param first The first element of the tuple
 * @param second The second element of the tuple
 * @param third The third element of the tuple
 * @return A t_tuple3 structure containing the three elements
 */
t_tuple3	tuple3_(t_u32 first, t_u32 second, t_u32 third)
{
	t_tuple3	res;

	res.first = first;
	res.second = second;
	res.third = third;
	return (res);
}

/**
 * tuple4_t - Creates a tuple structure with four elements
 *
 * @param tuple The tuple to copy
 * @return A t_tuple4 structure containing the four elements
 */
t_tuple4	tuple4_t(t_tuple4 tuple)
{
	t_tuple4	res;

	res.first = tuple.first;
	res.second = tuple.second;
	res.third = tuple.third;
	res.fourth = tuple.fourth;
	return (res);
}

/**
 * tuple4_ - Creates a tuple structure with four elements
 *
 * @param first The first element of the tuple
 * @param second The second element of the tuple
 * @param third The third element of the tuple
 * @param fourth The fourth element of the tuple
 * @return A t_tuple4 structure containing the four elements
 */
t_tuple4	tuple4_(t_u32 first, t_u32 second, t_u32 third, t_u32 fourth)
{
	t_tuple4	res;

	res.first = first;
	res.second = second;
	res.third = third;
	res.fourth = fourth;
	return (res);
}
