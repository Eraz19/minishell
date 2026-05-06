#include "builder.h"
#include "lr_machine.h"
#include <stdio.h>
#include <stdlib.h>

/*
Compile command:
ccc -Ilibft -Iincludes ${^$(find srcs/2_builder/1_lr_machine -type d | sort)/#/-I} $(find srcs/2_builder/1_lr_machine -name '*.c' | sort) main.c libft/libft.a -o test_lr
*/

int	main(void)
{
	t_lr_machine	machine;

	lr_machine_init(&machine);
	if (!lr_machine_build(&machine))
		return (EXIT_FAILURE);
	lr_machine_free(&machine);
	return (EXIT_SUCCESS);
}
