#ifndef TOKEN_POOL_H
# define TOKEN_POOL_H

# include "libft.h"
# include "error.h"

/* ************************************************************************* */
/*                             TYPE FORWARDING                               */
/* ************************************************************************* */

typedef struct s_token	t_token;

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

typedef t_vector		t_token_pool;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	token_pool_init(t_token_pool *pool);

void	token_pool_free_void(void *pool);
void	token_pool_free(t_token_pool *pool);

void	token_pool_clear(t_token_pool *pool);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	token_pool_deep_dup(void *dst, const void *src);

t_error	token_pool_push(t_token_pool *pool, t_token *token);

t_token	*token_pool_get(const t_token_pool *pool, size_t index);

void	token_pool_take(t_token_pool *pool, size_t index, t_token *dst);

t_error	token_pool_transfer(t_token_pool *dst, t_token_pool *src, size_t index);

#endif
