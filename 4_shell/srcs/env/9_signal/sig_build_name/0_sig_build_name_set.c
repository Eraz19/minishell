/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_sig_build_name_set.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:14 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_build_name_priv.h"

t_error	sig_build_name_set(const char *name, t_string *out_name)
{
	if (!string_init(out_name, 0, name, -1))
		return (error_sys());
	return (error(ERR_NO));
}
