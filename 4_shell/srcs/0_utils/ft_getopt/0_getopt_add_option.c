/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_getopt_add_option.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:47:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:47:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt_priv.h"

t_error	getopt_add_option(t_getopt_state *state, t_getopt_option *src)
{
	if (!vector_push(&state->out->options, src))
		return (error_sys());
	return (error(ERR_NO));
}
