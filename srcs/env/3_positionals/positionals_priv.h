#ifndef POSITIONALS_PRIV_H
# define POSITIONALS_PRIV_H

/**
 * @brief Free a positional frame for vector_free() callbacks.
 *
 * The @c void* signature matches @ref vector_free().
 *
 * @param positionals Positional frame to release (borrowed).
 */
void	positionals_free_item(void *positionals);

#endif
