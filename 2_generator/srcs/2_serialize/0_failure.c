#include <stdbool.h>
#include <stdio.h>

bool	serializer_report_failure(void)
{
	return (perror("serializer"), false);
}
