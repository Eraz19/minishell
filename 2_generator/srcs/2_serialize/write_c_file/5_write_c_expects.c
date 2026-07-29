#include "write_c_file_priv.h"
#include "generator_serialize_priv.h"
#include "logs.h"

#define EXPECT_VAR	"bool\t\t\texpects_cmd_name_or_word[LR_STATE_COUNT]"

static inline bool	generator_write_all_expects(
						int c_fd,
						const t_lr_generator *gen)
{
	size_t	count;
	size_t	i;

	count = gen->lr_states.len;
	i = 0;
	while (i < count)
	{
		if (!generator_write_zu(c_fd, NULL, gen->expects[i]))
			return (false);
		if (i < count - 1)
		{
			if (!generator_write(c_fd, ", "))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	generator_write_c_expects(int c_fd, const t_lr_generator *gen)
{
	if (!generator_write_c_var_start(c_fd, EXPECT_VAR))
		return (false);
	if (!generator_write_all_expects(c_fd, gen))
		return (false);
	if (!generator_write_c_var_end(c_fd))
		return (false);
	return (print_pass("expects generated\n"), true);
}
