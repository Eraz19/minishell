#ifndef QUALIFIERS_H
# define QUALIFIERS_H

# include "lr_machine_type.h"
# include "parser_type.h"
# include "token.h"

t_error	qualifiers_build_table(t_parser *parser, const t_lr_machine *machine);
t_error	parser_qualify_symbol(
			t_parser *parser,
			size_t lr_state_id,
			const t_token	*token);

#endif
