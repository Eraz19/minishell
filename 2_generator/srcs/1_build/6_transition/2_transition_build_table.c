#include "generator_transitions.h"
#include "generator_lr_state.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

#define LR_STATE_NOT_FOUND	"generator: internal error: lr state not found\n"

static inline bool	lr_state_not_found(void)
{
	(void)write(STDERR_FILENO, LR_STATE_NOT_FOUND, str_len(LR_STATE_NOT_FOUND));
	return (false);
}

static inline bool	build_initial_lr_state(
						const t_lr_generator *generator,
						t_lr_state *lr_states)
{
	t_rule_state	rule_state;
	t_lr_state		lr_state;

	lr_state_init(&lr_state);
	rule_state.rule_id = RULE_ACCEPT;
	rule_state.pos = 0;
	rule_state.lookahead = SYM_EOF;
	if (!lr_state_add_rule_state(&lr_state, &rule_state, NULL))
		return (lr_state_free(&lr_state), false);
	else if (!lr_state_complete(generator, &lr_state))
		return (lr_state_free(&lr_state), false);
	else if (!lr_state_add(lr_states, &lr_state, NULL))
		return (lr_state_free(&lr_state), false);
	return (true);
}

static inline bool	add_transition(
						t_lr_generator *generator,
						const t_lr_state *from_lr_state,
						t_symbol symbol,
						const t_lr_state *to_lr_state)
{
	t_transition	transition;
	size_t			from_id;
	size_t			to_id;

	if (!lr_state_find_id(&generator->lr_states, from_lr_state, &from_id))
		return (lr_state_not_found());
	if (!lr_state_find_id(&generator->lr_states, to_lr_state, &to_id))
		return (lr_state_not_found());
	transition.from_lr_state_id = from_id;
	transition.symbol = symbol;
	transition.to_lr_state_id = to_id;
	if (!vector_push(&generator->transitions, &transition))
		return (perror("generator"), false);
	return (true);
}

static inline bool	build_lr_state_and_transition(
						t_lr_generator *generator,
						const t_lr_state *lr_state_from,
						t_symbol symbol)
{
	t_lr_state	lr_state_new;
	bool		did_add;

	if (!lr_state_next(generator, &lr_state_new, lr_state_from, symbol))
		return (false);
	if (lr_state_new.len > 0)
	{
		did_add = false;
		if (!lr_state_add(&generator->lr_states, &lr_state_new, &did_add))
			return (lr_state_free(&lr_state_new), false);
		if (!add_transition(generator, lr_state_from, symbol, &lr_state_new))
		{
			if (did_add == false)
				lr_state_free(&lr_state_new);
			return (false);
		}
		if (did_add == false)
			lr_state_free(&lr_state_new);
	}
	else
		lr_state_free(&lr_state_new);
	return (true);
}

bool	transition_build_table(t_lr_generator *generator)
{
	size_t		i;
	t_symbol	symbol;
	t_lr_state	lr_state;

	if (!build_initial_lr_state(generator, &generator->lr_states))
		return (false);
	i = 0;
	while (i < generator->lr_states.len)
	{
		lr_state = ((const t_lr_state *)generator->lr_states.data)[i];
		symbol = 0;
		while (symbol < SYM_COUNT)
		{
			if (!build_lr_state_and_transition(generator, &lr_state, symbol))
				return (false);
			symbol++;
		}
		i++;
	}
	return (true);
}
