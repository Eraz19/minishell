#ifndef ACTION_H
# define ACTION_H

# include "builder.h"
# include "stdint.h"

# define ACTION_PAYLOAD_EMPTY	SIZE_MAX

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup action_pub Action module public API
 *  @brief Public functions used to initialize, build and release the ACTION
 *         table.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref rule_state, @ref lr_state,
 *           @ref transition, @ref goto. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module builds the terminal ACTION table stored in @ref t_lr_machine.
 */

/* ************************************************************************* */
/*                                   MACROS                                  */
/* ************************************************************************* */

/**
 * @ingroup action_pub
 * @brief Sentinel payload value used when an action has no meaningful payload.
 *
 * @note The default ACTION table initialization uses this value for
 *       @ref ACTION_ERROR entries.
 */
# define ACTION_PAYLOAD_EMPTY	SIZE_MAX

/* ************************************************************************* */
/*                                ACTION (PUB)                               */
/* ************************************************************************* */

/**
 * @ingroup action_pub
 * @brief Builds the ACTION table of an LR machine.
 *
 * This function first allocates and initializes the whole ACTION table with
 * default @ref ACTION_ERROR entries. It then fills terminal-labeled
 * transitions as @ref ACTION_SHIFT entries and completed rule states as
 * @ref ACTION_REDUCE entries. A completed start rule with lookahead
 * @ref SYM_EOF produces an @ref ACTION_ACCEPT entry.
 *
 * @note This function mutates the ACTION table stored in @p machine.
 * @note On success, ownership of the allocated ACTION table remains with
 *       @p machine and the table must later be released with @ref action_free.
 * @note The current implementation stores `rule_state.rule_id` as the payload
 *       of @ref ACTION_ACCEPT entries.
 *
 * @warning @p machine must NOT be NULL.
 * @warning `@p machine->rules`, `@p machine->lr_states`, and
 *          `@p machine->transitions` must already contain valid data,
 *          typically produced by @ref rules_build and
 *          @ref transition_build_table.
 * @warning This function does not free a previously allocated ACTION table
 *          before overwriting `@p machine->actions`.
 * @warning On failure, entries added before the error remain stored in
 *          @p machine. This function does not roll back partial progress.
 * @warning This function also fails on shift/reduce, reduce/reduce, or
 *          shift/accept conflicts. In that case, a diagnostic is printed and
 *          the function returns false.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose ACTION table must be allocated and
 *                populated (borrowed, must NOT be NULL).
 * @return true if the ACTION table was built successfully, false on allocation
 *         failure or parsing-table conflict.
 */
bool	action_build_table(t_lr_machine *machine);

/**
 * @ingroup action_pub
 * @brief Releases a previously allocated ACTION table.
 *
 * This function frees each row referenced by `*actions`, then frees the outer
 * table pointer and sets `*actions` to NULL.
 *
 * @note If @p actions is NULL or if `*actions` is NULL, this function does
 *       nothing.
 *
 * @warning When `*actions` is not NULL, @p lr_states_count must match the
 *          number of allocated rows in the table.
 *
 * @param lr_states_count Number of rows allocated in the table.
 * @param actions Address of the ACTION table pointer to release (borrowed, can
 *                be NULL).
 */
void	action_free(size_t lr_states_count, t_action ***actions);

/**
 * @ingroup action_pub
 * @brief Initializes an ACTION table pointer to an empty state.
 *
 * This function sets `*actions` to NULL.
 *
 * @warning @p actions must NOT be NULL.
 *
 * @param actions Address of the ACTION table pointer to initialize (borrowed,
 *                must NOT be NULL).
 */
void	action_init(t_action ***actions);

#endif
