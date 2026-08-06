/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_is_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:47:19 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:43:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "grammar_name.h"
#include <stdlib.h>

bool	name_is_valid_str(const t_string *name)
{
	return (name->len > 0 && name_is_valid(name->data));
}
