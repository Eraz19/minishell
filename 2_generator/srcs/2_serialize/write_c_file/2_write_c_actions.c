#include "write_c_file_priv.h"
#include "generator_serialize_priv.h"
#include "logs.h"

#define ACTION_VAR	"t_action\t\tactions[ACTION_COUNT]"

static inline bool	generator_write_c_action(int c_fd, const t_action *action)
{
	if (!generator_write_zu(c_fd, NULL, action->type))
		return (false);
	if (!generator_write(c_fd, ", "))
		return (false);
	return (generator_write_zu(c_fd, NULL, action->payload));
}

static inline bool	generator_write_all_actions(
						int c_fd,
						const t_lr_generator *gen)
{
	const t_action	*action;
	size_t			col_count;
	size_t			count;
	size_t			i;

	col_count = SYM_TERMINAL_MAX + 1;
	count = gen->lr_states.len * col_count;
	i = 0;
	while (i < count)
	{
		if (!generator_write_brack_start(c_fd))
			return (false);
		action = &gen->actions[i];
		if (!generator_write_c_action(c_fd, action))
			return (false);
		if (i < count - 1)
		{
			if (!generator_write_brack_end(c_fd))
				return (false);
		}
		else if (!generator_write_brack_last(c_fd))
			return (false);
		i++;
	}
	return (true);
}

bool	generator_write_c_actions(int c_fd, const t_lr_generator *gen)
{
	if (!generator_write_c_var_start(c_fd, ACTION_VAR))
		return (false);
	if (!generator_write_all_actions(c_fd, gen))
		return (false);
	if (!generator_write_c_var_end(c_fd))
		return (false);
	return (print_pass("actions generated\n"), true);
}
