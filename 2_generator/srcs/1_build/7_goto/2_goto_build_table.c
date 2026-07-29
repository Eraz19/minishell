#include "generator_goto.h"
#include "generator_transitions.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define GOTO_CONFLICT	"generator: internal error: goto conflict\n"
#define GOTO_TOO_BIG	"generator: gotos table size overflow\n"

static inline bool	goto_report_conflict(void)
{
	(void)write(STDERR_FILENO, GOTO_CONFLICT, str_len(GOTO_CONFLICT));
	return (false);
}

static inline bool	goto_malloc_table(size_t **gotos, size_t lr_states_count)
{
	size_t	col_count;

	col_count = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	if (col_count > SIZE_MAX / sizeof(**gotos)
		|| lr_states_count > SIZE_MAX / (col_count * sizeof(**gotos)))
	{
		(void)write(STDERR_FILENO, GOTO_TOO_BIG, str_len(GOTO_TOO_BIG));
		return (false);
	}
	*gotos = malloc(lr_states_count * col_count * sizeof(**gotos));
	if (*gotos == NULL)
		return (perror("generator"), false);
	return (true);
}

static inline void	goto_set_empty(size_t *gotos, size_t lr_states_count)
{
	size_t	col_count;
	size_t	table_size;
	size_t	i;

	col_count = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	table_size = lr_states_count * col_count;
	i = 0;
	while (i < table_size)
		gotos[i++] = GOTO_EMPTY;
}

static inline bool	goto_process_transitions(
						const t_transition *transitions,
						size_t transition_count,
						size_t *gotos)
{
	size_t		i;
	t_symbol	symbol;
	size_t		row;
	size_t		col;
	size_t		to_lr_state_id;

	i = 0;
	while (i < transition_count)
	{
		symbol = transitions[i].symbol;
		if (symbol >= SYM_NON_TERMINAL_MIN && symbol <= SYM_NON_TERMINAL_MAX)
		{
			row = transitions[i].from_lr_state_id;
			row *= SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
			col = symbol - SYM_NON_TERMINAL_MIN;
			to_lr_state_id = transitions[i].to_lr_state_id;
			if (gotos[row + col] != GOTO_EMPTY
				&& gotos[row + col] != to_lr_state_id)
				return (goto_report_conflict());
			gotos[row + col] = to_lr_state_id;
		}
		i++;
	}
	return (true);
}

bool	goto_build_table(
			const t_vector *transitions,
			size_t lr_states_count,
			size_t **gotos)
{
	if (!goto_malloc_table(gotos, lr_states_count))
		return (false);
	goto_set_empty(*gotos, lr_states_count);
	if (!goto_process_transitions(transitions->data, transitions->len, *gotos))
		return (goto_free(gotos), false);
	return (true);
}
