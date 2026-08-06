/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:48 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:23:49 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "walker.h"
#include "walker_priv.h"

t_error	walk(t_runner *runner, t_ast_root *ast_root)
{
	int	exit_status;

	exit_status = -1;
	return (walk_list(runner, ast_root, &exit_status));
}
