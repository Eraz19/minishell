/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:41:20 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:41:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"

t_error	builtin_colon(int argc, char **argv, t_runner *runner, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)runner;
	*exit_status = 0;
	return (error(ERR_NO));
}
