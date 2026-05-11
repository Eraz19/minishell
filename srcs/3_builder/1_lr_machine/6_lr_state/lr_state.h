#ifndef LR_STATE_H
# define LR_STATE_H

# include "builder.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup lr_state_pub LR state module public API
 *  @brief Public functions used to create, compare, register and derive
 *         @ref t_lr_state values.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref rule_state, @ref transition,
 *           @ref goto, @ref action. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module provides helpers for manipulating LR(1) states represented as
 *  sets of @ref t_rule_state values.
 */

/* ************************************************************************* */
/*                               LR_STATE (PUB)                              */
/* ************************************************************************* */

/**
 * @ingroup lr_state_pub
 * @brief Adds an LR state to a registry if it is not already present.
 *
 * This function searches @p lr_states for a state equal to @p lr_state using
 * @ref lr_state_find_id. If no equal state is found, it appends @p lr_state to
 * @p lr_states with @ref vector_push.
 *
 * @note Equality is tested with @ref lr_state_equal.
 * @note If the state already exists, this function returns true and leaves
 *       @p did_add unchanged.
 * @note If a new state is inserted and @p did_add is not NULL, `*did_add` is
 *       set to true.
 * @note Insertion copies the @ref t_lr_state structure into @p lr_states but
 *       does not duplicate the underlying rule-state buffer. After a
 *       successful insertion, that underlying storage must be considered owned
 *       by @p lr_states.
 *
 * @warning @p lr_states and @p lr_state must NOT be NULL.
 * @warning @p lr_states must be a valid vector storing @ref t_lr_state items.
 * @warning When @p did_add is not NULL, it must point to writable storage and
 *          must already have been initialized by the caller.
 * @warning After a successful insertion, caller must NOT free @p lr_state
 *          unless it knows the state was already present and therefore was not
 *          inserted.
 * @warning This function performs no parameter validation.
 *
 * @param lr_states LR-state registry to search and possibly extend
 *                  (borrowed, must NOT be NULL).
 * @param lr_state LR state to register (borrowed, underlying storage ownership
 *                 may transfer to @p lr_states on successful insertion, must
 *                 NOT be NULL).
 * @param did_add Optional flag set to true when a new state is inserted
 *                (borrowed, can be NULL).
 * @return ERR_NO / ERR_LIBC
 */
t_error	lr_state_add(t_vector *lr_states, t_lr_state *lr_state, bool *did_add);

/**
 * @ingroup lr_state_pub
 * @brief Adds a rule state to an LR state if it is not already present.
 *
 * This function checks whether @p rule_state is already contained in
 * @p lr_state. If not, it appends it to @p lr_state with @ref vector_push.
 *
 * @note Containment is tested using the same equality criteria as
 *       @ref rule_state_equal.
 * @note If @p rule_state is already present, this function returns true and
 *       leaves @p did_add unchanged.
 * @note If a new rule state is inserted and @p did_add is not NULL,
 *       `*did_add` is set to true.
 *
 * @warning @p lr_state must NOT be NULL.
 * @warning @p lr_state must be a valid vector storing @ref t_rule_state items.
 * @warning When @p did_add is not NULL, it must point to writable storage and
 *          must already have been initialized by the caller.
 * @warning This function performs no parameter validation.
 *
 * @param lr_state LR state to extend (borrowed, must NOT be NULL).
 * @param rule_state Rule state to insert if absent.
 * @param did_add Optional flag set to true when @p rule_state is newly added
 *                (borrowed, can be NULL).
 * @return ERR_NO / ERR_LIBC.
 */
t_error	lr_state_add_rule_state(t_lr_state *lr_state, t_rule_state rule_state,
			bool *did_add);

/**
 * @ingroup lr_state_pub
 * @brief Completes an LR state by computing its LR(1) closure.
 *
 * For each rule state currently stored in @p lr_state, this function examines
 * the next expected symbol. When that symbol is a non-terminal, all grammar
 * rules whose left-hand side matches that symbol are added with position 0 and
 * with lookaheads derived from the FIRST set of the remaining suffix and the
 * current lookahead.
 *
 * The process is repeated until no new rule state can be added.
 *
 * @note This function mutates @p lr_state in place.
 * @note Lookahead computation delegates to @ref first.
 * @note New rule states are inserted through @ref lr_state_add_rule_state.
 *
 * @warning @p machine and @p lr_state must NOT be NULL.
 * @warning @p machine->rules must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning The nullable-symbol table and FIRST table stored in @p machine must
 *          already have been built with @ref symbols_build_nullables_table and
 *          @ref first_build_table.
 * @warning Every rule state already stored in @p lr_state must contain a valid
 *          `rule_id`, `pos`, and `lookahead`.
 * @warning On failure, rule states added before the error remain stored in
 *          @p lr_state. This function does not roll back partial progress.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine providing grammar, nullable-symbol and FIRST data
 *                (borrowed, must NOT be NULL).
 * @param lr_state LR state to complete in place (borrowed, must NOT be NULL).
 * @return ERR_NO / ERR_LIBC.
 */
t_error	lr_state_complete(t_lr_machine *machine, t_lr_state *lr_state);

/**
 * @ingroup lr_state_pub
 * @brief Compares two LR states as unordered sets of rule states.
 *
 * This function returns true when @p a and @p b have the same length and every
 * rule state stored in @p a is also contained in @p b.
 *
 * @note The current implementation treats LR states as sets and ignores item
 *       ordering.
 * @note This comparison assumes each LR state contains no duplicate
 *       @ref t_rule_state values, as enforced by @ref lr_state_add_rule_state.
 *
 * @warning @p a and @p b must NOT be NULL.
 * @warning @p a and @p b must each be valid vectors storing
 *          @ref t_rule_state items.
 * @warning This function performs no parameter validation.
 *
 * @param a First LR state to compare (borrowed, must NOT be NULL).
 * @param b Second LR state to compare (borrowed, must NOT be NULL).
 * @return true if @p a and @p b represent the same set of rule states, false
 *         otherwise.
 */
bool	lr_state_equal(t_lr_state *a, t_lr_state *b);

/**
 * @ingroup lr_state_pub
 * @brief Searches a registry for the identifier of a given LR state.
 *
 * This function scans the LR-state registry stored in @p lr_states and
 * compares each entry with @p lr_state using @ref lr_state_equal.
 *
 * @note When the state is found and @p id is not NULL, `*id` receives the
 *       matching index.
 * @note When the state is not found, @p id is left unmodified.
 *
 * @warning @p lr_states and @p lr_state must NOT be NULL.
 * @warning @p lr_states must be a valid vector storing @ref t_lr_state items.
 * @warning This function performs no parameter validation.
 *
 * @param lr_states LR-state registry to search (borrowed, must NOT be NULL).
 * @param lr_state LR state to look up (borrowed, must NOT be NULL).
 * @param id Optional output receiving the matching registry index (borrowed,
 *           can be NULL).
 * @return true if a matching LR state was found, false otherwise.
 */
bool	lr_state_find_id(t_vector *lr_states, t_lr_state *lr_state, size_t *id);

/**
 * @ingroup lr_state_pub
 * @brief Releases the storage owned by an LR state.
 *
 * This function frees the dynamic storage owned by @p lr_state through
 * @ref vector_free.
 *
 * @warning @p lr_state must NOT be NULL.
 * @warning @p lr_state must previously have been initialized with
 *          @ref lr_state_init.
 *
 * @param lr_state LR state to release (borrowed, must NOT be NULL).
 */
void	lr_state_free(t_lr_state *lr_state);

/**
 * @ingroup lr_state_pub
 * @brief Initializes an empty LR state.
 *
 * This function initializes @p lr_state as a vector storing
 * @ref t_rule_state items.
 *
 * @warning @p lr_state must NOT be NULL.
 * @warning @p lr_state must not already own allocated storage. Free it first
 *          with @ref lr_state_free before reinitializing it.
 *
 * @param lr_state LR state to initialize (borrowed, must NOT be NULL).
 */
void	lr_state_init(t_lr_state *lr_state);

/**
 * @ingroup lr_state_pub
 * @brief Computes the next LR state reached by consuming a symbol.
 *
 * This function initializes @p dst, then scans every rule state stored in
 * @p src. For each rule state whose next expected symbol equals @p symbol,
 * the dot position is advanced by one and the resulting rule state is added to
 * @p dst. If at least one rule state is added, @p dst is then completed with
 * @ref lr_state_complete.
 *
 * @note On success, @p dst is always initialized by this function.
 * @note On success, @p dst may be empty when no rule state in @p src expects
 *       @p symbol.
 * @note On failure, any storage allocated for @p dst during this call is
 *       released before returning false.
 * @note The caller owns the resulting @p dst on success and must release it
 *       with @ref lr_state_free.
 *
 * @warning @p machine, @p dst and @p src must NOT be NULL.
 * @warning @p dst and @p src must not alias the same object.
 * @warning @p dst must not already own allocated storage.
 * @warning @p machine->rules must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning The nullable-symbol table and FIRST table stored in @p machine must
 *          already have been built with @ref symbols_build_nullables_table and
 *          @ref first_build_table.
 * @warning Every rule state stored in @p src must contain a valid `rule_id`,
 *          `pos`, and `lookahead`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine providing grammar, nullable-symbol and FIRST data
 *                (borrowed, must NOT be NULL).
 * @param dst Destination LR state receiving the result (owned by caller on
 *            success, must NOT be NULL).
 * @param src Source LR state to advance (borrowed, must NOT be NULL).
 * @param symbol Consumed grammar symbol.
 * @return ERR_NO / ERR_LIBC
 */
t_error	lr_state_next(t_lr_machine *machine, t_lr_state *dst, t_lr_state *src,
			t_symbol symbol);

/**
 * @ingroup lr_state_pub
 * @brief Releases an LR-state registry and all LR states stored in it.
 *
 * This function calls @ref lr_state_free on each @ref t_lr_state stored in
 * @p lr_states, then frees the registry storage itself with @ref vector_free.
 *
 * @warning @p lr_states must NOT be NULL.
 * @warning @p lr_states must previously have been initialized with
 *          @ref lr_state_table_init.
 * @warning @p lr_states must be a valid vector storing @ref t_lr_state items.
 *
 * @param lr_states LR-state registry to release (borrowed, must NOT be NULL).
 */
void	lr_state_table_free(t_lr_state *lr_states);

/**
 * @ingroup lr_state_pub
 * @brief Initializes an empty LR-state registry.
 *
 * This function initializes @p lr_states as a vector storing @ref t_lr_state
 * items.
 *
 * @warning @p lr_states must NOT be NULL.
 * @warning @p lr_states must not already own allocated storage. Free it first
 *          with @ref lr_state_table_free before reinitializing it.
 *
 * @param lr_states LR-state registry to initialize (borrowed, must NOT be
 *                  NULL).
 */
void	lr_state_table_init(t_lr_state *lr_states);

#endif
