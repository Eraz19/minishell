# include "libft.h"
# include "error.h"

/* -------------------- PUBLIC --------------- */

// + print mode ENV_PRINT_ALIAS 

t_error    env_print_one_alias(t_string *name);

t_error	env_alias_table_push(const t_string *alias_name, const t_string *value);
t_error	env_alias_table_get(
			const t_string *alias_name,
			t_string *out_value,
			bool add_to_stack);
t_error	env_alias_table_remove(const t_string *alias_name);

t_error	env_alias_stack_push(t_string *alias_name);
void	env_alias_stack_pop(void);

bool	env_alias_is_forbidden(const t_string *name);
void	env_alias_forbidden_clear(void);

/* -------------------- PRIVATE --------------- */

typedef t_hashmap 	t_alias_table;

// vector of t_string;
typedef t_vector	t_alias_stack;

// vector of t_string;
typedef t_vector	t_forbidden_aliases;

void	env_alias_table_init(void);
void	env_alias_table_clear(void);
void	env_alias_table_free(void);

void	env_alias_stack_init();
void	env_alias_stack_clear(void);
void	env_alias_stack_free(void);

void	env_alias_forbidden_init(void);
t_error	env_alias_forbidden_push(t_string *alias_name);
void	env_alias_forbidden_free(void);
