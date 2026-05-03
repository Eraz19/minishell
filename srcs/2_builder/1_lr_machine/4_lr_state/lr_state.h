#ifndef LR_STATE_H
# define LR_STATE_H

# include "parser.h"

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	lr_state_init(t_lr_state *lr_state);
void	lr_state_table_init(t_lr_state *lr_states);
void	lr_state_free(t_lr_state *lr_state);
void	lr_state_table_free(t_lr_state *lr_states);

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

bool	lr_state_equal(t_lr_state *a, t_lr_state *b);
// did_add can be NULL, if not, it must already be initialized by caller
bool	lr_state_add_rule_state(t_lr_state *lr_state, t_rule_state rule_state, bool *did_add);
bool	lr_state_find_id(t_vector *lr_states, t_lr_state *lr_state, size_t *id);
bool	lr_state_add(t_vector *lr_states, t_lr_state *lr_state, bool *did_add);

/* ************************************************************************* */
/*                                    CORE                                   */
/* ************************************************************************* */

// Completes an lr_state by adding all implied rule_states (aka closure() in LR parsing theory)
bool	lr_state_complete(t_rule *rules, t_lr_state *lr_state);
// Computes the next lr_state reached from `src` by consuming `symbol` (aka goto_set() in LR parsing theory)
bool	lr_state_next(t_rule *rules, t_lr_state *dst, t_lr_state *src, t_symbol symbol);

#endif
