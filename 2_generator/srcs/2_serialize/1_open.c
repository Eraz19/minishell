#include "generator_serialize_priv.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#define H_PATH		"3_lr_tables/2_generated/lr_tables.h"
#define C_PATH		"3_lr_tables/2_generated/lr_tables.c"
#define ERR_PREFIX	"serializer: unable to open "

bool	generator_open(int *out_h_fd, int *out_c_fd)
{
	int		oflag;
	mode_t	omode;

	*out_h_fd = -1;
	*out_c_fd = -1;
	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	omode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	*out_h_fd = open(H_PATH, oflag, omode);
	if (*out_h_fd < 0)
		return (perror(ERR_PREFIX H_PATH), false);
	*out_c_fd = open(C_PATH, oflag, omode);
	if (*out_c_fd < 0)
	{
		perror(ERR_PREFIX C_PATH);
		(void)close(*out_h_fd);
		*out_h_fd = -1;
		return (false);
	}
	return (true);
}
