#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// TODO: stub ASM
time_t	get_now_unix_seconds(void)
{
	struct stat	stat;
	int			fds[2];

	if (pipe(fds) == -1)
		return (-1);
	if (fstat(fds[0], &stat) == -1)
		return (close(fds[0]), close(fds[1]), -1);
	return (close(fds[0]), close(fds[1]), stat.st_mtime);
}
