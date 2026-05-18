#include "debug.h"

const char	*bool_to_string(bool value)
{
	if (value)
		return ("true");
	return ("false");
}
