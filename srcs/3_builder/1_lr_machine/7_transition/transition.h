#ifndef TRANSITION_H
# define TRANSITION_H

# include "builder.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup transition_pub Transition module public API
 *  @brief Public functions used to initialize, build and release LR
 *         transitions.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref rule_state, @ref lr_state,
 *           @ref goto, @ref action. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module builds the transition table stored in @ref t_lr_machine and
 *  populates the associated LR-state registry.
 */

/* ************************************************************************* */
/*                              TRANSITION (PUB)                             */
/* ************************************************************************* */

/**
 * @ingroup transition_pub
 * @brief Builds the LR transition table of a machine.
 *
 * This function first creates the initial LR state from @ref RULE_START_1 with
 * lookahead @ref SYM_EOF, completes it with @ref lr_state_complete, and stores
 * it in `@p machine->lr_states`. It then explores every symbol in the range
 * `[0, @ref SYM_COUNT)` from every discovered LR state, computes successor
 * states with @ref lr_state_next, registers newly discovered states with
 * @ref lr_state_add, and appends the corresponding @ref t_transition entries
 * to `@p machine->transitions`.
 *
 * @note This function mutates both `@p machine->lr_states` and
 *       `@p machine->transitions`.
 * @note Newly discovered LR states are stored in `@p machine->lr_states` and
 *       reused by transition entries through their numeric identifiers.
 *
 * @warning @p machine must NOT be NULL.
 * @warning `@p machine->rules` must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning The nullable-symbol table and FIRST table stored in @p machine must
 *          already have been built with @ref symbols_build_nullables_table and
 *          @ref first_build_table.
 * @warning `@p machine->lr_states` and `@p machine->transitions` must already
 *          have been initialized with @ref lr_state_table_init and
 *          @ref transition_init.
 * @warning This function is intended to build tables from an empty state. It
 *          does not clear previously stored LR states or transitions before
 *          appending new data.
 * @warning On failure, LR states and transitions added before the error remain
 *          stored in @p machine. This function does not roll back partial
 *          progress.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose LR-state registry and transition table must
 *                be built (borrowed, must NOT be NULL).
 * @return true if the transition table was built successfully, false on
 *         allocation failure or internal inconsistency.
 */
bool	transition_build_table(t_lr_machine *machine);

/**
 * @ingroup transition_pub
 * @brief Releases the storage owned by a transition table.
 *
 * This function frees the vector storage owned by @p transitions through
 * @ref vector_free.
 *
 * @note @ref t_transition items do not own nested dynamic resources.
 *
 * @warning @p transitions must NOT be NULL.
 * @warning @p transitions must previously have been initialized with
 *          @ref transition_init.
 *
 * @param transitions Transition table to release (borrowed, must NOT be NULL).
 */
void	transition_free(t_vector *transitions);

/**
 * @ingroup transition_pub
 * @brief Initializes an empty transition table.
 *
 * This function initializes @p transitions as a vector storing
 * contiguous @ref t_transition items.
 *
 * @note This function cannot fail with the current implementation because it
 *       delegates to @ref vector_init with a zero initial capacity.
 *
 * @warning @p transitions must NOT be NULL.
 * @warning @p transitions must not already own allocated storage. Free it
 *          first with @ref transition_free before reinitializing it.
 *
 * @param transitions Transition table to initialize (borrowed, must NOT be
 *                    NULL).
 */
void	transition_init(t_vector *transitions);

#endif
