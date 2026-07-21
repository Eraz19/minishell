#ifndef QUALIFIERS_H
# define QUALIFIERS_H

# include "lr_machine_type.h"

t_error	qualifiers_build_table(
			t_qualifier **qualifiers,
			const t_lr_machine *machine);

#endif
