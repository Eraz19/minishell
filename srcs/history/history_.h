#ifndef HISTORY__H
# define HISTORY__H

#include "history.h"

/**
 * @ingroup history
 * @brief Resolves the history file path from the environment.
 *
 * Reads @c $HISTFILE when it is set and non-empty, otherwise falls back to
 * @c $HOME/.sh_history when @c HOME is available. If neither variable yields a
 * usable path, leaves the file path empty, prints a warning and
 * disables persistent history.
 *
 * @param state Pointer to the history state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_load_path_env(t_history *state);

/**
 * @ingroup history
 * @brief Resolves the history size cap from the environment.
 *
 * Reads @c $HISTSIZE into @p state->rl_history.max. An unset or empty value
 * means unlimited (-1); any non-negative value below 128 is raised to 128.
 *
 * @param state Pointer to the history state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_load_size_env(t_history *state);

/**
 * @ingroup history
 * @brief Builds the file content buffer from the persisted tail and pending
 * input.
 *
 * Serialises and concatenates the list entries from index @p start onward,
 * then appends the currently typed line when it is non-empty, into
 * @p state->file.content, replacing any previous content.
 *
 * @param state Pointer to the history state (borrowed).
 * @param start Index of the first list entry to include.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_build_file_content(t_history *state, size_t start);

#endif
