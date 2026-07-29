#include "generator.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

int	main(void)
{
	t_lr_generator	generator;
	int				res;

	print_start(99, "LR GENERATOR");
	generator_init(&generator);
	print_title("generator_build_tables()");
	if (generator_build_tables(&generator) == true)
		res = EXIT_SUCCESS;
	else
		res = EXIT_FAILURE;
	print_result("generator_build_tables()");
	generator_free(&generator);
	print_stop();
	return (res);
}
