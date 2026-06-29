#include "variables.h"
#include <stdlib.h>
#include <unistd.h>
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

#define PS1_NAME	"PS1"
#define PS1_VALUE	"$ "
#define PS2_NAME	"PS2"
#define PS2_VALUE	"> "
#define PS4_NAME	"PS4"
#define PS4_VALUE	"+ "

static inline void	up_build_ps1(t_string *out_name, t_string *out_value)
{
	static char	name[] = PS1_NAME;
	static char	value[] = PS1_VALUE;
	size_t		len;

	assert(out_name != NULL);
	assert(out_value != NULL);
	len = sizeof(PS1_NAME);
	string_take(out_name, name, len + 1, len);
	len = sizeof(PS1_VALUE);
	string_take(out_value, value, len + 1, len);
}

static inline void	up_build_ps2(t_string *out_name, t_string *out_value)
{
	static char	name[] = PS2_NAME;
	static char	value[] = PS2_VALUE;
	size_t		len;

	assert(out_name != NULL);
	assert(out_value != NULL);
	len = sizeof(PS2_NAME);
	string_take(out_name, name, len + 1, len);
	len = sizeof(PS2_VALUE);
	string_take(out_value, value, len + 1, len);
}

static inline void	up_build_ps4(t_string *out_name, t_string *out_value)
{
	static char	name[] = PS4_NAME;
	static char	value[] = PS4_VALUE;
	size_t		len;

	assert(out_name != NULL);
	assert(out_value != NULL);
	len = sizeof(PS4_NAME);
	string_take(out_name, name, len + 1, len);
	len = sizeof(PS4_VALUE);
	string_take(out_value, value, len + 1, len);
}

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	var_init_target_up(t_string *name, t_string *value)
{
	t_error		err;
	t_string	current_value;

	assert(name != NULL);
	assert(value != NULL);
	err = var_get(name, &current_value);
	if (err.type == ERR_NO)
	{
		string_free(&current_value);
		return (error(ERR_NO));
	}
	if (err.type == ERR_VAR_NOT_FOUND)
		err = var_set(name, value, false, false);
	if (err.type == ERR_NO)
		print_pass("'%s' has been set to '%s'\n", name->data, value->data);
	return (err);
}

/*
3. Initialize [UP] defaults if you support User Portability Utilities
	- PS1 = "$ " if absent
	- PS2 = "> " if absent
	- PS4 = "+ " if absent
*/
t_error	var_load_up(void)
{
	t_string	name;
	t_string	value;
	t_error		err;

	up_build_ps1(&name, &value);
	err = var_init_target_up(&name, &value);
	if (err.type != ERR_NO)
		return (err);
	up_build_ps2(&name, &value);
	err = var_init_target_up(&name, &value);
	if (err.type != ERR_NO)
		return (err);
	up_build_ps4(&name, &value);
	return (var_init_target_up(&name, &value));
}
