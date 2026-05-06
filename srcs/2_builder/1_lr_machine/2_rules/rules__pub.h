#ifndef RULES_H
# define RULES_H

# include "builder.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup rules_pub Rules module public API
 *  @brief Public functions used to initialize and build the grammar rule table.
 *
 *  This module populates the parser grammar stored as an array of @ref t_rule
 *  entries.
 */

/* ************************************************************************* */
/*                                 RULES (PUB)                               */
/* ************************************************************************* */

/**
 * @ingroup rules_pub
 * @brief Builds the full grammar rule table.
 *
 * Fills the rule array referenced by @p rules with all grammar productions
 * supported by the LR machine, including production left-hand sides,
 * right-hand sides, right-hand-side lengths, and optional semantic hooks.
 *
 * @note This function writes entries identified by the various @ref t_rule_id
 *       constants.
 * @note The storage pointed to by @p rules remains owned by the caller.
 * @note The built table is intended to contain @ref RULE_COUNT entries.
 *
 * @warning @p rules must NOT be NULL.
 * @warning @p rules must reference writable storage large enough to contain
 *          exactly @ref RULE_COUNT @ref t_rule entries.
 * @warning This function does not perform any parameter validation.
 * @warning This function assumes the caller provides a rule table intended for
 *          this grammar layout.
 *
 * @param rules Rule table to populate (borrowed, must NOT be NULL).
 */
void	rules_build(t_rule *rules);

/**
 * @ingroup rules_pub
 * @brief Initializes the grammar rule table to an empty state.
 *
 * Sets the whole rule table referenced by @p rules to zero over
 * @ref RULE_COUNT entries.
 *
 * @note This clears every field of each @ref t_rule entry before the table is
 *       populated by @ref rules_build.
 * @note The storage pointed to by @p rules remains owned by the caller.
 *
 * @warning @p rules must NOT be NULL.
 * @warning @p rules must reference writable storage large enough to contain
 *          exactly @ref RULE_COUNT @ref t_rule entries.
 * @warning This function does not perform any parameter validation.
 *
 * @param rules Rule table to initialize (borrowed, must NOT be NULL).
 */
void	rules_init(t_rule *rules);

#endif
