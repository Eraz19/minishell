#ifndef VAR_LOAD_MANDATORY_PRIV_H
# define VAR_LOAD_MANDATORY_PRIV_H

# include "error.h"

/**
 * @brief Set the IFS mandatory variable.
 *
 * @return `ERR_VAR_INVALID_NAME`, `ERR_VAR_READ_ONLY` or `ERR_LIBC`.
 */
t_error	var_set_ifs(void);

/**
 * @brief Validate whether a PWD value is acceptable.
 *
 * @param pwd Candidate PWD value (borrowed, read-only).
 * @param res Receives the validation result (borrowed).
 * @return `ERR_LIBC`.
 */
t_error	var_pwd_is_valid(const char *pwd, bool *res);

/**
 * @brief Set the PWD mandatory variable.
 *
 * @return `ERR_VAR_INVALID_NAME`, `ERR_VAR_READ_ONLY` or `ERR_LIBC`.
 */
t_error	var_set_pwd(void);

/**
 * @brief Set the PPID mandatory variable.
 *
 * @return `ERR_VAR_INVALID_NAME`, `ERR_VAR_READ_ONLY` or `ERR_LIBC`.
 */
t_error	var_set_ppid(void);

#endif
