#include "parser.h"
#include "lr_machine.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	t_lr_machine	machine;

	lr_machine_init(&machine);
	if (!lr_machine_build(&machine))
		return (EXIT_FAILURE);
	lr_machine_free(&machine);
	return (EXIT_SUCCESS);
}
