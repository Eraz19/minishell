#ifndef CMD_RESOLVER_H
# define CMD_RESOLVER_H

# include "error.h"
# include "cmd_type.h"
# include "token.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// TODO: doc
t_error	cmd_resolve(t_cmd *cmd, const t_token_pool *words);

#endif
