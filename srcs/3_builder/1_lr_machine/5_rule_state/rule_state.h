#ifndef RULE_STATE_H
# define RULE_STATE_H

# include "builder.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup rule_state_pub Rule state module public API
 *  @brief Public functions used to inspect and compare @ref t_rule_state
 *         values.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref lr_state, @ref transition,
 *           @ref goto, @ref action. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module provides helpers for comparing rule states (aka LR items) 
 *  and querying their progression within a rule.
 */

/* ************************************************************************* */
/*                              RULE_STATE (PUB)                             */
/* ************************************************************************* */

/**
 * @ingroup rule_state_pub
 * @brief Compares two rule states for exact equality.
 *
 * Two @ref t_rule_state values are considered equal when their `rule_id`,
 * `pos`, and `lookahead` fields are all equal.
 *
 * @note This function does not access external state.
 *
 * @param a First rule state to compare.
 * @param b Second rule state to compare.
 * @return true if @p a and @p b are equal, false otherwise.
 */
bool		rule_state_equal(t_rule_state a, t_rule_state b);

/**
 * @ingroup rule_state_pub
 * @brief Reports whether a rule state has reached the end of its rule.
 *
 * A rule state is considered complete when @p rule_state.pos is greater than
 * or equal to the right-hand-side length of the rule designated by
 * @p rule_state.rule_id in @p rules.
 *
 * @warning @p rules must NOT be NULL.
 * @warning @p rule_state.rule_id must designate a valid rule index in the
 *          range `[0, @ref RULE_COUNT)`.
 * @warning This function performs no parameter validation.
 *
 * @param rules Rule table to inspect (borrowed, must NOT be NULL).
 * @param rule_state Rule state to test.
 * @return true if @p rule_state is complete, false otherwise.
 */
bool		rule_state_is_complete(t_rule *rules, t_rule_state rule_state);

/**
 * @ingroup rule_state_pub
 * @brief Returns the next symbol expected by a rule state.
 *
 * When @p rule_state is not complete, this function returns the symbol located
 * at position @p rule_state.pos in the right-hand side of the rule designated
 * by @p rule_state.rule_id in @p rules.
 *
 * @note When @p rule_state is complete, this function returns @ref SYM_error.
 *
 * @warning @p rules must NOT be NULL.
 * @warning @p rule_state.rule_id must designate a valid rule index in the
 *          range `[0, @ref RULE_COUNT)`.
 * @warning This function performs no parameter validation.
 *
 * @param rules Rule table to inspect (borrowed, must NOT be NULL).
 * @param rule_state Rule state to inspect.
 * @return The next expected symbol, or @ref SYM_error if @p rule_state is
 *         complete.
 */
t_symbol	rule_state_next_symbol(t_rule *rules, t_rule_state rule_state);

#endif
