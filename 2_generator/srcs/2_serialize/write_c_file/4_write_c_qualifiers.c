#include "write_c_file_priv.h"
#include "generator_serialize_priv.h"
#include "logs.h"
#include <unistd.h>

#define QUALIFIERS_VAR	"t_qualifier\tqualifiers[LR_STATE_COUNT]"
#define QUALIFY_NONE	"NULL"
#define QUALIFY_WORD	"qualify_word"
#define QUALIFY_1		"qualify_1"
#define QUALIFY_2		"qualify_2"
#define QUALIFY_4		"qualify_4"
#define QUALIFY_5		"qualify_5"
#define QUALIFY_6A		"qualify_6a"
#define QUALIFY_6B		"qualify_6b"
#define QUALIFY_7A		"qualify_7a"
#define QUALIFY_7B		"qualify_7b"

static inline bool	generator_report_unknown_qualifier(void)
{
	(void)generator_write(STDERR_FILENO, "serializer: unknown qualifier\n");
	return (false);
}

static inline const char	*generator_get_qualifier_name(t_qualifier qualifier)
{
	if (qualifier == NULL)
		return (QUALIFY_NONE);
	else if (qualifier == qualify_word)
		return (QUALIFY_WORD);
	else if (qualifier == qualify_1)
		return (QUALIFY_1);
	else if (qualifier == qualify_2)
		return (QUALIFY_2);
	else if (qualifier == qualify_4)
		return (QUALIFY_4);
	else if (qualifier == qualify_5)
		return (QUALIFY_5);
	else if (qualifier == qualify_6a)
		return (QUALIFY_6A);
	else if (qualifier == qualify_6b)
		return (QUALIFY_6B);
	else if (qualifier == qualify_7a)
		return (QUALIFY_7A);
	else if (qualifier == qualify_7b)
		return (QUALIFY_7B);
	return (NULL);
}

static inline bool	generator_write_all_qualifiers(
						int c_fd,
						const t_lr_generator *gen)
{
	const char	*name;
	size_t		count;
	size_t		i;

	count = gen->lr_states.len;
	i = 0;
	while (i < count)
	{
		name = generator_get_qualifier_name(gen->qualifiers[i]);
		if (name == NULL)
			return (generator_report_unknown_qualifier());
		if (!generator_write(c_fd, name))
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

bool	generator_write_c_qualifiers(int c_fd, const t_lr_generator *gen)
{
	if (!generator_write_c_var_start(c_fd, QUALIFIERS_VAR))
		return (false);
	if (!generator_write_all_qualifiers(c_fd, gen))
		return (false);
	if (!generator_write_c_var_end(c_fd))
		return (false);
	return (print_pass("qualifiers generated\n"), true);
}
