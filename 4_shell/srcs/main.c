/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:24:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:24:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern char	**environ;

int	main(int argc, char **argv)
{
	return (shell_run(argc, argv, environ, true));
}
