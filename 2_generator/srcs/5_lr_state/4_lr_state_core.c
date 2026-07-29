#include "generator_lr_state.h"
#include "generator_first.h"
#include "generator_rule_state.h"
#include "generator.h"

static inline void	compute_first(
						const t_lr_generator *generator,
						t_first_param *first_param,
						const t_rule_state *rule_state)
{
	const t_rule	*rule;

	rule = &generator->rules[rule_state->rule_id];
	if (rule_state->pos >= rule->rhs_len)
	{
		first_param->symbols = NULL;
		first_param->count = 0;
	}
	else
	{
		first_param->symbols = rule->rhs + (rule_state->pos + 1);
		first_param->count = rule->rhs_len - (rule_state->pos + 1);
	}
	first_param->has_lookahead = true;
	first_param->lookahead = rule_state->lookahead;
	first(generator->first, generator->nullable_symbols, first_param);
}

static inline bool	add_variants(
						t_lr_state *lr_state,
						t_rule_state *rule_state,
						const t_first_param *first,
						bool *did_add)
{
	t_symbol	terminal;

	terminal = 0;
	while (terminal <= SYM_TERMINAL_MAX)
	{
		if (first->result[terminal] == true)
		{
			rule_state->lookahead = terminal;
			if (lr_state_add_rule_state(lr_state, rule_state, did_add) == false)
				return (false);
		}
		terminal++;
	}
	return (true);
}

static inline bool	compute_rule_state(
						const t_lr_generator *generator,
						t_lr_state *lr_state,
						t_rule_state *rule_state,
						bool *did_add)
{
	t_symbol		next_sym;
	t_first_param	first_param;
	size_t			rule_id;
	const t_rule	*rule;

	next_sym = rule_state_next_symbol(generator->rules, rule_state);
	if (next_sym < SYM_NON_TERMINAL_MIN || next_sym > SYM_NON_TERMINAL_MAX)
		return (true);
	compute_first(generator, &first_param, rule_state);
	rule_id = 0;
	while (rule_id < RULE_COUNT)
	{
		rule = &generator->rules[rule_id];
		if (rule->lhs == next_sym)
		{
			rule_state->rule_id = rule_id;
			rule_state->pos = 0;
			if (!add_variants(lr_state, rule_state, &first_param, did_add))
				return (false);
		}
		rule_id++;
	}
	return (true);
}

bool	lr_state_complete(const t_lr_generator *generator, t_lr_state *lr_state)
{
	t_rule_state	rule_state;
	bool			did_add;
	size_t			i;

	did_add = true;
	while (did_add)
	{
		did_add = false;
		i = 0;
		while (i < lr_state->len)
		{
			rule_state = ((const t_rule_state *)lr_state->data)[i];
			if (!compute_rule_state(generator, lr_state, &rule_state, &did_add))
				return (false);
			i++;
		}
	}
	return (true);
}

bool	lr_state_next(
			const t_lr_generator *generator,
			t_lr_state *dst,
			const t_lr_state *src,
			t_symbol symbol)
{
	size_t			i;
	t_rule_state	rule_state;
	t_symbol		next_symbol;

	lr_state_init(dst);
	i = 0;
	while (i < src->len)
	{
		rule_state = ((const t_rule_state *)src->data)[i++];
		next_symbol = rule_state_next_symbol(generator->rules, &rule_state);
		if (next_symbol != symbol)
			continue ;
		rule_state.pos++;
		if (lr_state_add_rule_state(dst, &rule_state, NULL) == false)
			return (lr_state_free(dst), false);
	}
	if (dst->len > 0)
	{
		if (lr_state_complete(generator, dst) == false)
			return (lr_state_free(dst), false);
	}
	return (true);
}
