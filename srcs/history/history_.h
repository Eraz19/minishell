#ifndef HISTORY__H
# define HISTORY__H

#include "history.h"

/**
 * @ingroup history
 * @brief Resolves the history file path from the environment.
 *
 * Reads $HISTFILE, falling back to $HOME/.sh_history when it is unset, and
 * stores the resulting path in state->file.path.
 *
 * @param state Pointer to the history state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_load_path_env(t_history *state);

/**
 * @ingroup history
 * @brief Resolves the history size cap from the environment.
 *
 * Reads $HISTSIZE into state->rl_history.max. An unset value means unlimited
 * (-1); any non-negative value below 128 is raised to 128.
 *
 * @param state Pointer to the history state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_load_size_env(t_history *state);

/**
 * @ingroup history
 * @brief Builds the file content buffer from the list tail.
 *
 * Serialises and concatenates the list entries from index @p start onward
 * into state->file.content, replacing any previous content.
 *
 * @param state Pointer to the history state (borrowed).
 * @param start Index of the first list entry to include.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_build_file_content(t_history *state, size_t start);

#endif
