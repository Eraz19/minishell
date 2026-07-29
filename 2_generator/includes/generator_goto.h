#ifndef GENERATOR_GOTO_H
# define GENERATOR_GOTO_H

# include "grammar_symbols.h"
# include "libft.h"
# include <stdint.h>

# define GOTO_EMPTY	SIZE_MAX

/*
For performance and const-casting purposes, gotos table is contigously alloc'd.
Therefore, instead of accessing it via gotos[lr_state][non-terminal_symbol],
it must be accessed via gotos[row + col] where:
- row = lr_state * (SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1)
- col = symbol - SYM_NON_TERMINAL_MIN
*/

void	goto_init(size_t **gotos);
void	goto_free(size_t **gotos);

bool	goto_build_table(
			const t_vector *transitions,
			size_t lr_states_count,
			size_t **gotos);
bool	go_to(
			const size_t *gotos,
			size_t current_lr_state_id,
			t_symbol symbol,
			size_t *new_lr_state_id);

#endif
