#include "libft.h"
#include "grammar_name.h"
#include <stdlib.h>
#include <assert.h>	// DEBUG

bool	name_is_valid_str(const t_string *name)
{
	assert(name != NULL);
	return (name->len > 0 && name_is_valid(name->data));
}
