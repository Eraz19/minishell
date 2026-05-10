#ifndef GOTO_H
# define GOTO_H

# include "builder.h"
# include <stdint.h>

# define GOTO_EMPTY	SIZE_MAX

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup goto_pub Goto module public API
 *  @brief Public functions used to initialize, build, query and release the
 *         GOTO table.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref rule_state, @ref lr_state,
 *           @ref transition, @ref action. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module builds the non-terminal transition table stored in
 *  @ref t_lr_machine and provides lookup helpers for it.
 */

/* ************************************************************************* */
/*                                 GOTO (PUB)                                */
/* ************************************************************************* */

/**
 * @ingroup goto_pub
 * @brief Looks up the next LR state reached through a non-terminal symbol.
 *
 * This function queries the GOTO table referenced by @p gotos for the entry
 * designated by @p current_lr_state_id and @p symbol. The symbol is converted
 * to a column index relative to @ref SYM_NON_TERMINAL_MIN.
 *
 * @note On success, the object pointed to by @p new_lr_state_id receives the
 *       destination LR-state identifier.
 * @note On failure, the object pointed to by @p new_lr_state_id is left
 *       unmodified.
 *
 * @warning @p gotos and @p new_lr_state_id must NOT be NULL.
 * @warning @p gotos must reference a valid table previously built by
 *          @ref goto_build_table.
 * @warning @p current_lr_state_id must be a valid row index in the GOTO table.
 * @warning @p symbol must be a non-terminal symbol in the range
 *          [@ref SYM_NON_TERMINAL_MIN, @ref SYM_NON_TERMINAL_MAX].
 * @warning This function performs no parameter validation except checking
 *          whether @p symbol is within the non-terminal range and whether the
 *          selected entry equals @ref GOTO_EMPTY.
 *
 * @param gotos GOTO table to query (borrowed, must NOT be NULL).
 * @param current_lr_state_id Source LR-state identifier.
 * @param symbol Non-terminal symbol to follow.
 * @param new_lr_state_id Output pointer receiving the destination LR-state
 *                        identifier (borrowed, must NOT be NULL).
 * @return true if a destination LR state exists for this transition, false
 *         otherwise.
 */
bool	go_to(size_t **gotos, size_t current_lr_state_id, t_symbol symbol,
			size_t *new_lr_state_id);

/**
 * @ingroup goto_pub
 * @brief Builds the GOTO table stored in an LR machine.
 *
 * This function allocates a two-dimensional table whose row count equals
 * `@p machine->lr_states.len` and whose column count equals the number of
 * non-terminal symbols from @ref SYM_NON_TERMINAL_MIN to
 * @ref SYM_NON_TERMINAL_MAX, inclusive. Every entry is first initialized to
 * @ref GOTO_EMPTY. The table is then populated from the transitions stored in
 * `@p machine->transitions`: only transitions labeled with non-terminal
 * symbols are copied into the resulting GOTO table.
 *
 * @note On success, ownership of the allocated table remains with @p machine
 *       and the table must later be released with @ref goto_free.
 * @note On allocation failure, this function frees any partially allocated
 *       rows and leaves `@p machine->gotos` set to NULL.
 *
 * @warning @p machine must NOT be NULL.
 * @warning `@p machine->lr_states` and `@p machine->transitions` must already
 *          have been built, typically by @ref transition_build_table.
 * @warning This function does not free a previously allocated GOTO table
 *          before overwriting `@p machine->gotos`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose GOTO table must be allocated and populated
 *                (borrowed, must NOT be NULL).
 * @return true if the table was built successfully, false on allocation
 *         failure.
 */
bool	goto_build_table(t_lr_machine *machine);

/**
 * @ingroup goto_pub
 * @brief Releases a previously allocated GOTO table.
 *
 * This function frees each row referenced by `*gotos`, then frees the outer
 * table pointer and sets `*gotos` to NULL.
 *
 * @note If @p gotos is NULL or if `*gotos` is NULL, this function does
 *       nothing.
 *
 * @warning When `*gotos` is not NULL, @p lr_states_count must match the number
 *          of allocated rows in the table.
 *
 * @param lr_states_count Number of rows allocated in the table.
 * @param gotos Address of the GOTO table pointer to release (borrowed, can be
 *              NULL).
 */
void	goto_free(size_t lr_states_count, size_t ***gotos);

/**
 * @ingroup goto_pub
 * @brief Initializes a GOTO table pointer to an empty state.
 *
 * This function sets `*gotos` to NULL.
 *
 * @warning @p gotos must NOT be NULL.
 *
 * @param gotos Address of the GOTO table pointer to initialize (borrowed,
 *              must NOT be NULL).
 */
void	goto_init(size_t ***gotos);

#endif
