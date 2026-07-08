#ifndef CMD_H
# define CMD_H

# include "cmd_type.h"

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initialize an empty executor command object.
 *
 * @note @p cmd is initialized by the function.
 *
 * @param cmd Destination command object (borrowed, initialized by the
 *            function).
 */
void	cmd_init(t_cmd *cmd);

/**
 * @brief Release every resource stored in an executor command object.
 *
 * @param cmd Command object to free (borrowed).
 */
void	cmd_free(t_cmd *cmd);

#endif
