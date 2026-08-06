/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:09:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:38:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"
#include "generator_serialize.h"
#include <stdlib.h>

static inline int	generator_exit(t_lr_generator *gen)
{
	generator_free(gen);
	return (EXIT_FAILURE);
}

int	main(void)
{
	t_lr_generator	generator;

	generator_init(&generator);
	if (!generator_build_tables(&generator))
		return (generator_exit(&generator));
	if (!generator_serialize(&generator))
		return (generator_exit(&generator));
	generator_free(&generator);
	return (EXIT_SUCCESS);
}
