#include "parser.h"
#include "lr_machine.h"
#include <stdio.h>

int	main(void)
{
	t_lr_machine	machine;

	lr_machine_init(&machine);
	if (!lr_machine_build(&machine))
		printf("💥 OOPS, lr_machine_build() failed 🙈\n");
	lr_machine_free(&machine);
}
