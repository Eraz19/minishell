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
 * @brief Encodes an entry for on-disk storage.
 *
 * Wraps *entry in single quotes and backslash-escapes any embedded quote,
 * replacing *entry with the freshly allocated encoded string and freeing the
 * original.
 *
 * @param entry In/out pointer to the entry to encode (owned; replaced on
 *              success).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	history_entry_serialize(char **entry);

/**
 * @ingroup history
 * @brief Decodes, in place, an entry read from disk.
 *
 * Removes the backslash escapes inserted by history_entry_serialize() from
 * *entry; the surrounding quotes are stripped earlier by
 * history_file_extract().
 *
 * @param entry In/out pointer to the entry to decode in place.
 */
void	history_entry_deserialize(char **entry);

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
