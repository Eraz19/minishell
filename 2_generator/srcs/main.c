/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:09:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:09:25 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"
#include "generator_serialize.h"
#include <stdlib.h>
#include "logs.h"	// DEBUG

static inline int	generator_exit(t_lr_generator *gen)
{
	generator_free(gen);
	print_stop();
	return (EXIT_FAILURE);
}

int	main(void)
{
	t_lr_generator	generator;

	print_start(99, "LR GENERATOR");
	generator_init(&generator);
	print_title("generator_build_tables()");
	if (!generator_build_tables(&generator))
		return (generator_exit(&generator));
	print_result("generator_build_tables()");
	print_title("generator_serialize()");
	if (!generator_serialize(&generator))
		return (generator_exit(&generator));
	print_result("generator_serialize()");
	generator_free(&generator);
	print_stop();
	return (EXIT_SUCCESS);
}
