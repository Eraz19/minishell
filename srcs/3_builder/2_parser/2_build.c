#include "qualifiers.h"
#include "parser.h"
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	parser_build_qualifiers_table(
			t_parser *parser,
			const t_lr_machine *machine)
{
	t_error	err;

	assert(parser != NULL);
	print_title(__func__, "()");
	err = qualifiers_build_table(parser, machine);
	print_pass("qualifiers table built                 (entries: %'6zu)\n", machine->lr_states.len);
	print_result(__func__, "()");
	return (err);
}
