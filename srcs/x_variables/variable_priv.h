#ifndef VARIABLE_PRIV_H
# define VARIABLE_PRIV_H

# include "variable.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup var_priv Variable Internal API
 *  @brief Internal helpers used by the variable module implementation.
 *
 *  @warning These functions are intended for intra-module use only.
 */

/* ************************************************************************* */
/*                                  PRIVATE                                  */
/* ************************************************************************* */

// TODO: add documentation
int	ft_getppid(void);
t_error	var_set_ifs(t_var_list *variables);
t_error	var_set_pwd(t_var_list *variables);
t_error	var_set_ppid(t_var_list *variables);
t_error	var_update_value(t_var *var, const char *value);

#endif
