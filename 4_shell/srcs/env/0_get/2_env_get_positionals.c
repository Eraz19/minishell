/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_env_get_positionals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:50:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	env_get_positionals(const t_positionals **dst)
{
	t_params	*params;

	params = shell_get_params();
	return (positionals_get(&params->positionals_stack, dst));
}
