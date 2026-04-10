/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tuple.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:39:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:44:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TUPLE_H
# define LIBFT_TUPLE_H

# include "libft_types.h"

typedef struct s_tuple2
{
	t_u32	first;
	t_u32	second;
}	t_tuple2;
typedef struct s_tuple3
{
	t_u32	first;
	t_u32	second;
	t_u32	third;
}	t_tuple3;
typedef struct s_tuple4
{
	t_u32	first;
	t_u32	second;
	t_u32	third;
	t_u32	fourth;
}	t_tuple4;

t_tuple3	tuple3_t(t_tuple3 tuple);
t_tuple4	tuple4_t(t_tuple4 tuple);
t_tuple2	tuple2_(t_u32 first, t_u32 second);
t_tuple3	tuple3_(t_u32 first, t_u32 second, t_u32 third);
t_tuple4	tuple4_(t_u32 first, t_u32 second, t_u32 third, t_u32 fourth);

#endif
