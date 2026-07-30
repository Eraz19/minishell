#include "utils.h"
#include <stdlib.h>

void	free_char_ptr_void(void *ptr)
{
	free(*(char **)ptr);
}
