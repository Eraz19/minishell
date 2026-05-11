#include "builder.h"
#include "lr_machine.h"

void	builder_init(t_builder *builder)
{
	lr_machine_init(&builder->lr_machine);
}

t_error	builder_load(t_builder *builder)
{
	return (lr_machine_build(&builder->lr_machine));
}

void	builder_free(t_builder *builder)
{
	lr_machine_free(&builder->lr_machine);
}
