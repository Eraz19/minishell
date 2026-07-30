#ifndef ALIAS_H
# define ALIAS_H

# include "error.h"
# include "libft.h"
# include "parser_type.h"
# include "alias_stack.h"

typedef struct s_alias
{
	t_error			err;
	bool			disable_position;
}	t_alias;


t_error    env_alias_table_push(const t_string *alias_name, const t_string *value);
t_error    env_alias_table_get(
            const t_string *alias_name,
            t_string *out_value,
            bool add_to_stack);
t_error    env_alias_table_remove(const t_string *alias_name);

t_error    env_alias_stack_push(t_string *alias_name);
void       env_alias_stack_pop(void);

bool       env_alias_is_forbidden(const t_string *name);
void       env_alias_forbidden_clear(void);


env_print(PARAMS_PRINT_ALIAS)
env_print_one_alias(name) (t_string *)

#endif
