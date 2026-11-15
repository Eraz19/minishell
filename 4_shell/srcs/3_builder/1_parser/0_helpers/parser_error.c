/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:06:36 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:06:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parser_priv.h"
#include <stdlib.h>

t_error	parser_internal_error(t_error err)
{
	return (error_print(err, "parser", "internal error", NULL, NULL));
}

t_error	parser_invalid_syntax(void)
{
	return (error_print(error(ERR_POSIX_SYNTAX), "parser", NULL, NULL));
}
