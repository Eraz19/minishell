/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_cmd_resolve_is_declaration_utility.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:02 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:57:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_resolve_priv.h"

bool	cmd_resolve_is_declaration_utility(const char *name)
{
	return (str_cmp(name, "export") == 0 || str_cmp(name, "readonly") == 0);
}
